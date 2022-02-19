// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"

#include "CharacterAnimations.generated.h"

class UCharacterAnimInstance;

UCLASS()
class ARCHER_API UCharacterAnimations : public UActorComponent
{
	GENERATED_BODY()

public:
	void Initialize(UCharacterAnimInstance* animInstance);
	void SetLocomotionState(ECharacterLocomotionState State) const;
	void SetAttackState(ECharacterAttackState State) const;
	void SetOrientationType(EOrientationType OrientationType);

private:
	UPROPERTY()
	UCharacterAnimInstance* AnimInstance;
};
