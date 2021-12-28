#pragma once
#include "ArcherMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ARCHER_API UArcherMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UArcherMovement();

	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	void MoveForward(float Value) const;
	void MoveRight(float Value) const;

	void SetMovementComponent(UPawnMovementComponent* MovementComponent);

private:
	class APlayerCameraManager* CameraManager;
	class UPawnMovementComponent* MovementComponent;
};
