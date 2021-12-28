#include "ArcherMovement.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UArcherMovement::UArcherMovement()
{
	UE_LOG(LogTemp, Warning, TEXT("constructor"));
}

void UArcherMovement::BeginPlay()
{
	Super::InitializeComponent();

	UE_LOG(LogTemp, Warning, TEXT("InitializeComponent"));
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("InitializeComponent"));
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}

void UArcherMovement::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(LogTemp, Warning, TEXT("InitializeComponent"));
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("InitializeComponent"));
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}


void UArcherMovement::MoveForward(float Value) const
{
	const FVector ForwardVector = CameraManager->GetActorForwardVector();
	const FVector UpVector = CameraManager->GetActorUpVector();
	const FVector ProjectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(ForwardVector, UpVector);
	
	MovementComponent->AddInputVector(ProjectedForward * Value);
}

void UArcherMovement::MoveRight(float Value) const
{
	const FVector rightVector = CameraManager->GetActorRightVector();
	const FVector upVector = CameraManager->GetActorUpVector();
	const FVector projectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(rightVector, upVector);
	
	MovementComponent->AddInputVector(projectedForward * Value);

}

void UArcherMovement::SetMovementComponent(UPawnMovementComponent* movementComponent)
{
	MovementComponent = movementComponent;
}
