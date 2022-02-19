// Copyright (c) Guillem Serra. All Rights Reserved.

#include "CharacterAnimations.h"

#include "CharacterAnimInstance.h"

void UCharacterAnimations::Initialize(UCharacterAnimInstance* animInstance)
{
	this->AnimInstance = animInstance;
}

void UCharacterAnimations::SetLocomotionState(ECharacterLocomotionState State) const
{
	if(!AnimInstance) return;

	AnimInstance->SetLocomotionState(State);
}

void UCharacterAnimations::SetAttackState(ECharacterAttackState State) const
{
	if(!AnimInstance) return;

	AnimInstance->SetAttackState(State);
}

void UCharacterAnimations::SetOrientationType(EOrientationType OrientationType)
{
	if(!AnimInstance) return;

	AnimInstance->SetOrientationType(OrientationType);
}
