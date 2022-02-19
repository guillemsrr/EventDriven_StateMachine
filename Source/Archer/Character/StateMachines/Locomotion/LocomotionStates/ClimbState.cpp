// Copyright (c) Guillem Serra. All Rights Reserved.

#include "ClimbState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"

void FClimbState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Climbing);
}

void FClimbState::End()
{
}
