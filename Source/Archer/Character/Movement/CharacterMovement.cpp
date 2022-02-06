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

FVector FCharacterMovement::GetCameraRelativeForwardVector() const
{
	const FVector ForwardVector = CameraManager->GetActorForwardVector();
	return GetProjectedVector(ForwardVector);
}

FVector FCharacterMovement::GetCameraRelativeRightVector() const
{
	const FVector RightVector = CameraManager->GetActorRightVector();
	return GetProjectedVector(RightVector);
}

void FCharacterMovement::MoveForward(float Value) const
{
	FVector ProjectedVector = GetCameraRelativeForwardVector();
	MovementComponent->AddInputVector(ProjectedVector * Value);
}

void FCharacterMovement::MoveRight(float Value) const
{
	const FVector ProjectedVector = GetCameraRelativeRightVector();
	MovementComponent->AddInputVector(ProjectedVector * Value);
}

FVector FCharacterMovement::GetProjectedVector(const FVector Vector) const
{
	FVector ProjectedVector = UKismetMathLibrary::ProjectVectorOnToPlane(Vector, FVector::UpVector);
	ProjectedVector.Normalize();
	return ProjectedVector;
}

/**
 * @brief For some reason, I can't name CameraManager parameter and property equally
 */
void FCharacterMovement::SetCameraManager(APlayerCameraManager* cameraManager)
{
	this->CameraManager = cameraManager;
}

void FCharacterMovement::SetWalkSpeed() const
{
	MovementComponent->MaxWalkSpeed = WalkSpeed;
}

void FCharacterMovement::SetRunSpeed() const
{
	MovementComponent->MaxWalkSpeed = RunSpeed;
}
