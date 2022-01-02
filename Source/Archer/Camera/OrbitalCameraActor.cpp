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

	AArcherPlayerCameraManager* CameraManager = Cast<AArcherPlayerCameraManager>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->AddOrbitalCameraReference(this);
	CameraManager->SetViewTarget(this);
	CameraManager->SetCurrentCamera(this);
	
	Camera->SetRelativeLocation(FVector(-15*Zoom, 0, 15*Zoom));
	LookAtRoot();
}

void AOrbitalCameraActor::LookAtRoot()
{
	FVector RootDirection = -Camera->GetRelativeLocation();
	RootDirection.Normalize();
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
	ProjectedForward.Normalize();
	
	FVector RotationVector = GetActorRotation().Vector();
	RotationVector += ProjectedForward/100.f*Value * RotationSpeed;

	FRotator Rotation = GetActorRotation();
	Rotation.Pitch -= Value * RotationSpeed;
	SetActorRelativeRotation(Rotation);
	CorrectRollRotation();
	//LookAtRoot();
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

	CorrectRollRotation();
	//LookAtRoot();
}
