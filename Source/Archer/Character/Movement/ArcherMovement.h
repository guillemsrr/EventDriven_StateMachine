#pragma once
#include "ArcherMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ARCHER_API UArcherMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UArcherMovement();
	
	void MoveForward(float Value) const;
	void MoveRight(float Value) const;

	void SetMovementComponent(UPawnMovementComponent* MovementComponent);

private:
	class UPawnMovementComponent* MovementComponent;
};
