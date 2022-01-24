#include "ArcherCharacter.h"

#include "Archer/Camera/PrecisionCameraActor.h"
#include "Archer/TimeManagement/SlowTimeManager.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mechanics/ArchTrace.h"
#include "Movement/CharacterMovement.h"
#include "Mechanics/CharacterMechanics.h"
#include "StateMachine/StateMachine.h"

AArcherCharacter::AArcherCharacter()
{
	ArcherMovement = new FCharacterMovement(GetCharacterMovement());
	Arch = CreateDefaultSubobject<UArchTrace>(TEXT("ArchTrace"));
	CharacterMechanics = new FCharacterMechanics(Arch);
	this->StateMachine = new FStateMachine(this);
}

AArcherCharacter::~AArcherCharacter()
{
	delete StateMachine;
	delete ArcherMovement;
	delete CharacterMechanics;
}

void AArcherCharacter::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(this);
	//Arch->Initialize(TimeManager);
}

void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();

	//TODO-> initialize in constructor?
	APrecisionCameraActor* Camera = GetWorld()->SpawnActor<APrecisionCameraActor>(
		APrecisionCameraActor::StaticClass(), GetActorLocation() + FVector(20, 0, 0), GetActorRotation());
	Camera->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	Arch->SetBowSocket(GetMesh());

	ArcherMovement->SetCameraManager(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
}

void AArcherCharacter::TickActor(float DeltaTime, ELevelTick Tick, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, Tick, ThisTickFunction);
}

void AArcherCharacter::EnableMovement() const
{
	StateMachine->SetWalkState();
}

void AArcherCharacter::DisableMovement() const
{
	StateMachine->SetSlowmoState();
}

FRotator AArcherCharacter::GetAimRotator() const
{
	return Arch->GetAimRotator();
}

FRotator AArcherCharacter::GetAimRotationRelativeToMovement() const
{
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GetVelocity());
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
}

void AArcherCharacter::MoveForward(const float Value)
{
	StateMachine->MoveForwardDelegate.Broadcast(Value);
}

void AArcherCharacter::MoveRight(const float Value)
{
	StateMachine->MoveRightDelegate.Broadcast(Value);
}

void AArcherCharacter::StartRunning()
{
	StateMachine->StartRunDelegate.Broadcast();
}

void AArcherCharacter::StopRunning()
{
	StateMachine->StopRunDelegate.Broadcast();
}

void AArcherCharacter::Aim()
{
	StateMachine->StartAimDelegate.Broadcast();
}

void AArcherCharacter::StopAim()
{
	StateMachine->StopAimDelegate.Broadcast();
}

void AArcherCharacter::StartShoot()
{
	//TODO handle it through delegates?
	StateMachine->StartShootDelegate.Broadcast();
}

void AArcherCharacter::ReleaseShoot()
{
	//TODO handle it through delegates?
	StateMachine->ReleaseShootDelegate.Broadcast();
	
	Arch->Shoot(ProjectileClass);
}

void AArcherCharacter::StartFreeAim()
{
	//StateMachine->StartFreeAimDelegate.Broadcast();
	Arch->SetFreeAim();
}

void AArcherCharacter::StopFreeAim()
{
	//StateMachine->StopFreeAimDelegate.Broadcast();
	Arch->SetAutoAim();
}
