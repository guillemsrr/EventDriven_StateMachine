// Copyright (c) Guillem Serra. All Rights Reserved.

#include "EmptyState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FEmptyState::Begin()
{
	MechanicsStateMachine->GetCharacterAnimations()->SetAttackState(ECharacterAttackState::NotAiming);
	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::Movement);
}

void FEmptyState::End()
{
}

void FEmptyState::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(0, -1, FColor::Green, "EmptyState");
}
