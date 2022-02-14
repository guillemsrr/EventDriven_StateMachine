#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationSlots.h"
#include "CharacterAnimationStates.h"
#include "Animation/AnimInstance.h"

#include "CharacterAnimInstance.generated.h"

UCLASS()
class ARCHER_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UCharacterAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;

	void PlayAnimationInSlot(UAnimSequence* AnimSequence, ECharacterAnimationSlots AnimationSlot);
	FORCEINLINE void SetLocomotionState(ECharacterLocomotionState animationState) { LocomotionState = animationState; }
	FORCEINLINE void SetAttackState(ECharacterAttackState attackState) { AttackState = attackState; }
	void SetOrientationType(EOrientationType Orientation);

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class AArcherCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	ECharacterLocomotionState LocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	ECharacterAttackState AttackState;

	EOrientationType OrientationType;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsMoving;

	//Offset yaw used for strafing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Movement)
	float MovementOffsetYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Movement)
	float LastMovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Turn in place")
	float RootYawOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Turn in place")
	float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Turn in place")
	FRotator AimRotation;

	float RotationCurve;
	float RotationCurveLastFrame;

private:
	float CurrentCharacterYaw;
	float LastCharacterYaw;
	TMap<ECharacterAnimationSlots, FName> SlotNames;
	
	void CheckMovement();
	void TurnInPlace();
};
