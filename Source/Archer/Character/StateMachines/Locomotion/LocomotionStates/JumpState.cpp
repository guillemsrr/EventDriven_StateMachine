#include "JumpState.h"

#include "Archer/Character/StateMachine/StateMachine.h"

void JumpState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Jumping);
}

void JumpState::End()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Normal);
}
