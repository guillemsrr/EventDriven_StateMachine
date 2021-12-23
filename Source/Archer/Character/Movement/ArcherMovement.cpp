#include "ArcherMovement.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UArcherMovement::UArcherMovement()
{
}

void UArcherMovement::MoveForward(float Value) const
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (!CameraManager)
	{
		return;
	}

	const FVector forwardVector = CameraManager->GetActorForwardVector();
	const FVector upVector = CameraManager->GetActorUpVector();
	const FVector projectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(forwardVector, upVector);
	
	MovementComponent->AddInputVector(projectedForward * Value);
}

void UArcherMovement::MoveRight(float Value) const
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (!CameraManager)
	{
		return;
	}

	const FVector rightVector = CameraManager->GetActorRightVector();
	const FVector upVector = CameraManager->GetActorUpVector();
	const FVector projectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(rightVector, upVector);
	
	MovementComponent->AddInputVector(projectedForward * Value);

}

void UArcherMovement::SetMovementComponent(UPawnMovementComponent* movementComponent)
{
	MovementComponent = movementComponent;
}
