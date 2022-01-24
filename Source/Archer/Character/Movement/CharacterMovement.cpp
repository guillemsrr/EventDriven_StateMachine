#include "CharacterMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"


FCharacterMovement::FCharacterMovement(UCharacterMovementComponent* MovementComponent)
{
	this->MovementComponent = MovementComponent;

	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	MovementComponent->JumpZVelocity = 1000.f;
}

void FCharacterMovement::MoveForward(float Value) const
{
	const FVector ForwardVector = CameraManager->GetActorForwardVector();
	FVector ProjectedVector = UKismetMathLibrary::ProjectVectorOnToPlane(ForwardVector, FVector::UpVector);
	ProjectedVector.Normalize();
	MovementComponent->AddInputVector(ProjectedVector * Value);
}

void FCharacterMovement::MoveRight(float Value) const
{
	const FVector RightVector = CameraManager->GetActorRightVector();
	FVector ProjectedVector = UKismetMathLibrary::ProjectVectorOnToPlane(RightVector, FVector::UpVector);
	ProjectedVector.Normalize();
	
	MovementComponent->AddInputVector(ProjectedVector * Value);
}

/**
 * @brief For some reason, I can't name CameraManager parameter and property equally
 */
void FCharacterMovement::SetCameraManager(APlayerCameraManager* cameraManager)
{
	this->CameraManager = cameraManager;
}

void FCharacterMovement::SetSpeed(float Speed) const
{
	MovementComponent->MaxWalkSpeed = Speed;
}
