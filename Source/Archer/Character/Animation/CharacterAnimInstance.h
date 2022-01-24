
#pragma once

#include "CoreMinimal.h"
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

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class AArcherCharacter* Character;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsSprinting;

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

	void TurnInPlace();
};
