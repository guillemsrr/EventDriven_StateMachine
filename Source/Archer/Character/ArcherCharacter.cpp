#include "ArcherCharacter.h"

#include "Archer/Camera/PrecisionCameraActor.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mechanics/ArchTrace.h"
#include "Movement/ArcherMovement.h"


AArcherCharacter::AArcherCharacter()
{
	CharacterMovement = CreateDefaultSubobject<UArcherMovement>(TEXT("Movement"));
	CharacterMovement->SetMovementComponent(GetMovementComponent());
	Arch = CreateDefaultSubobject<UArchTrace>(TEXT("ArchTrace"));
	//ArchTrace->RegisterComponent();
	CameraActor = CreateDefaultSubobject<APrecisionCameraActor>("Camera");
	CameraActor->SetActorRelativeLocation(FVector(50, 50, 50));
	CameraActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 1000.f;
}

void AArcherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AArcherCharacter::MoveForward).bConsumeInput = false;
	PlayerInputComponent->BindAxis("MoveRight", this, &AArcherCharacter::MoveRight).bConsumeInput = false;
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AArcherCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AArcherCharacter::StopAim);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AArcherCharacter::StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AArcherCharacter::ReleaseShoot);
}

void AArcherCharacter::MoveForward(const float Value)
{
	CharacterMovement->MoveForward(Value);
}

void AArcherCharacter::MoveRight(const float Value)
{
	CharacterMovement->MoveRight(Value);
}

void AArcherCharacter::Aim()
{
	Arch->Aim();
}

void AArcherCharacter::StopAim()
{
	Arch->StopAiming();
}

void AArcherCharacter::StartShoot()
{
	Arch->Shoot(ProjectileClass);
}

void AArcherCharacter::ReleaseShoot()
{
	//Arch->Shoot();
}

