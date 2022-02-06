#pragma once

class APlayerCameraManager;
class UCharacterMovementComponent;

class FCharacterMovement
{
public:
	explicit FCharacterMovement(UCharacterMovementComponent* MovementComponent);
	FVector GetCameraRelativeForwardVector() const;
	FVector GetCameraRelativeRightVector() const;

	void MoveForward(float Value) const;
	void MoveRight(float Value) const;
	void SetCameraManager(APlayerCameraManager* cameraManager);
	void SetWalkSpeed() const;
	void SetRunSpeed() const;

private:
	const float WalkSpeed = 500.f;
	const float RunSpeed = 800.f;

	APlayerCameraManager* CameraManager;
	UCharacterMovementComponent* MovementComponent;
	
	FVector GetProjectedVector(FVector Vector) const;
};
