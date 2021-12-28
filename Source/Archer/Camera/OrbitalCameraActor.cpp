#include "OrbitalCameraActor.h"

#include "ArcherPlayerCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AOrbitalCameraActor::AOrbitalCameraActor()
{
}

void AOrbitalCameraActor::BeginPlay()
{
	Super::BeginPlay();

	AArcherPlayerCameraManager* CameraManager = static_cast<AArcherPlayerCameraManager*>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->AddOrbitalCameraReference(this);
	CameraManager->SetViewTarget(this);
	CameraManager->SetCurrentCamera(this);

	Camera->SetRelativeLocation(FVector(-1500, 0, 1500));
	LookAtRoot();
}

void AOrbitalCameraActor::LookAtRoot()
{
	FVector RootDirection = -Camera->GetRelativeLocation();
	RootDirection.Normalize(0.1f);
	Camera->SetRelativeRotation(RootDirection.Rotation());
}

void AOrbitalCameraActor::SetupPlayerInputComponent()
{
	Super::SetupPlayerInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AOrbitalCameraActor::RotateCameraUpDown).bConsumeInput = false;
	InputComponent->BindAxis("MoveRight", this, &AOrbitalCameraActor::RotateCameraLeftRight).bConsumeInput = false;
}

void AOrbitalCameraActor::CorrectRollRotation()
{
	FRotator Rotation = GetActorRotation();
	Rotation.Roll =0.f;
	SetActorRotation(Rotation);
}

void AOrbitalCameraActor::RotateCameraUpDown(float Value)
{
	if(Value == 0.f)
	{
		return;
	}

	const FVector ForwardVector = Camera->GetForwardVector();
	const FVector UpVector =  Camera->GetUpVector();
	FVector ProjectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(ForwardVector, UpVector);
	ProjectedForward.Normalize(0.1f);
	
	FVector RotationVector = GetActorRotation().Vector();
	RotationVector += ProjectedForward/100.f*Value * RotationSpeed;
	//SetActorRotation(RotationVector.Rotation());
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, GetActorRotation().ToString());

	FRotator Rotation = GetActorRotation();
	Rotation.Pitch -= Value * RotationSpeed;
	SetActorRelativeRotation(Rotation);

	//LookAtRoot();
	//CorrectRollRotation();
}

void AOrbitalCameraActor::RotateCameraLeftRight(float Value)
{
	if(Value == 0.f)
	{
		return;
	}
	
	FRotator Rotation = GetActorRotation();
	Rotation.Yaw -= Value * RotationSpeed;
	SetActorRelativeRotation(Rotation);

	//LookAtRoot();
	//CorrectRollRotation();
}
