#include "ArcherMovement.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UArcherMovement::UArcherMovement()
{
	//UE_LOG(LogTemp, Warning, TEXT("constructor"));
}

void UArcherMovement::BeginPlay()
{
	Super::InitializeComponent();

	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("InitializeComponent"));
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}


void UArcherMovement::MoveForward(float Value) const
{
	if(!IsMovementEnabled) return;
	
	const FVector ForwardVector = CameraManager->GetActorForwardVector();
	const FVector UpVector = CameraManager->GetActorUpVector();
	FVector ProjectedVector = UKismetMathLibrary::ProjectVectorOnToPlane(ForwardVector, FVector::UpVector);
	ProjectedVector.Normalize();

	
	MovementComponent->AddInputVector(ProjectedVector * Value);
}

void UArcherMovement::MoveRight(float Value) const
{
	if(!IsMovementEnabled) return;

	const FVector RightVector = CameraManager->GetActorRightVector();
	const FVector UpVector = CameraManager->GetActorUpVector();
	FVector ProjectedVector = UKismetMathLibrary::ProjectVectorOnToPlane(RightVector, FVector::UpVector);
	ProjectedVector.Normalize();
	
	MovementComponent->AddInputVector(ProjectedVector * Value);

}

void UArcherMovement::SetMovementComponent(UPawnMovementComponent* movementComponent)
{
	MovementComponent = movementComponent;
}
