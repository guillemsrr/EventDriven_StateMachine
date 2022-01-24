#pragma once

class APlayerCameraManager;
class UCharacterMovementComponent;

class FCharacterMovement
{
public:
	explicit FCharacterMovement(UCharacterMovementComponent* MovementComponent);

	void MoveForward(float Value) const;
	void MoveRight(float Value) const;
	void SetCameraManager(APlayerCameraManager* cameraManager);
	void SetSpeed(float Speed) const;

private:
	APlayerCameraManager* CameraManager;
	UCharacterMovementComponent* MovementComponent;
};
