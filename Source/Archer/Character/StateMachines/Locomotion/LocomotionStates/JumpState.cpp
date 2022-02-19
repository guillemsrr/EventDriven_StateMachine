// Copyright (c) Guillem Serra. All Rights Reserved.

#include "JumpState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"

void FJumpState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Jumping);
}

void FJumpState::End()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Normal);
}
