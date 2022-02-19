// Copyright (c) Guillem Serra. All Rights Reserved.

#include "ArcherCharacter.h"

#include "Animation/CharacterAnimInstance.h"
#include "Archer/Camera/PrecisionCameraActor.h"
#include "Archer/TimeManagement/SlowTimeManager.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mechanics/ArchTrace.h"
#include "Movement/CharacterMovement.h"
#include "Mechanics/CharacterMechanics.h"
#include "StateMachines/Locomotion/LocomotionStateMachine.h"
#include "StateMachines/Mechanics/MechanicsStateMachine.h"

PRAGMA_DISABLE_OPTIMIZATION

AArcherCharacter::AArcherCharacter()
{
	ArcherMovement = new FCharacterMovement(GetCharacterMovement());
	Arch = CreateDefaultSubobject<UArchTrace>(TEXT("ArchTrace"));
	CharacterAnimations = CreateDefaultSubobject<UCharacterAnimations>(TEXT("CharacterAnimations"));
	CharacterAnimations->Initialize(Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance()));
	CharacterMechanics = new FCharacterMechanics(Arch, CharacterAnimations);
	LocomotionStateMachine = new FLocomotionStateMachine(this);
	MechanicsStateMachine = new FMechanicsStateMachine(this);
	
	bUseControllerRotationYaw = false;
}

AArcherCharacter::~AArcherCharacter()
{
	delete LocomotionStateMachine;
	delete ArcherMovement;
	delete CharacterMechanics;
}

void AArcherCharacter::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(this);
	TimeManager->AddFreeTicker(Arch);
}

void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();

	//TODO-> initialize in constructor?
	APrecisionCameraActor* Camera = GetWorld()->SpawnActor<APrecisionCameraActor>(
		APrecisionCameraActor::StaticClass(), GetActorLocation() + FVector(20, 0, 0), GetActorRotation());
	Camera->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Arch->SetBowSocket(GetMesh());
	CharacterAnimations->Initialize(Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance()));
	CharacterMechanics->SetProjectile(ProjectileClass);
	ArcherMovement->SetCameraManager(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	PlayerController = static_cast<AArcherPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));
}

void AArcherCharacter::TickActor(float DeltaTime, ELevelTick Tick, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, Tick, ThisTickFunction);

	MechanicsStateMachine->Tick(DeltaTime);
}

void AArcherCharacter::EnableMovement() const
{
	LocomotionStateMachine->SetWalkState();
	MechanicsStateMachine->SetAimReadyState();
}

void AArcherCharacter::DisableMovement() const
{
	LocomotionStateMachine->SetSlowmoState();
	MechanicsStateMachine->SetAimReadyState();
}

FRotator AArcherCharacter::GetAimRotator() const
{
	return Arch->GetAimRotator();
}

FRotator AArcherCharacter::GetAimRotationRelativeToMovement() const
{
	const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GetVelocity());
	return UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, GetAimRotator());
}

void AArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward).bConsumeInput = false;
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight).bConsumeInput = false;
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ThisClass::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ThisClass::StopRunning);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ThisClass::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ThisClass::StopAim);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ThisClass::StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ThisClass::ReleaseShoot);
	PlayerInputComponent->BindAction("FreeAimMode", IE_Pressed, this, &ThisClass::StartFreeAim);
	PlayerInputComponent->BindAction("FreeAimMode", IE_Released, this, &ThisClass::StopFreeAim);
	PlayerInputComponent->BindAxis("PrecisionAimX", this, &ThisClass::PrecisionAimX);
	PlayerInputComponent->BindAxis("PrecisionAimY", this, &ThisClass::PrecisionAimY);
}

void AArcherCharacter::MoveForward(const float Value)
{
	LocomotionStateMachine->MoveForwardDelegate.Broadcast(Value);
}

void AArcherCharacter::MoveRight(const float Value)
{
	LocomotionStateMachine->MoveRightDelegate.Broadcast(Value);
}

void AArcherCharacter::StartRunning()
{
	LocomotionStateMachine->StartRunDelegate.Broadcast();
}

void AArcherCharacter::StopRunning()
{
	LocomotionStateMachine->StopRunDelegate.Broadcast();
}

void AArcherCharacter::Aim()
{
	MechanicsStateMachine->StartAimingDelegate.Broadcast();
}

void AArcherCharacter::StopAim()
{
	MechanicsStateMachine->StopAimingDelegate.Broadcast();
}

void AArcherCharacter::StartShoot()
{
	MechanicsStateMachine->StartShootingDelegate.Broadcast();
}

void AArcherCharacter::ReleaseShoot()
{
	MechanicsStateMachine->StopShootingDelegate.Broadcast();
}

void AArcherCharacter::StartFreeAim()
{
	MechanicsStateMachine->StartFreeAimDelegate.Broadcast();
}

void AArcherCharacter::StopFreeAim()
{
	MechanicsStateMachine->StopFreeAimDelegate.Broadcast();
}

void AArcherCharacter::PrecisionAimX(float Value)
{
	MechanicsStateMachine->AimXValueDelegate.Broadcast(Value);
}

void AArcherCharacter::PrecisionAimY(float Value)
{
	MechanicsStateMachine->AimYValueDelegate.Broadcast(Value);
}

PRAGMA_ENABLE_OPTIMIZATION