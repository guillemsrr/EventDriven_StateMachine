#include "ClimbState.h"

#include "Archer/Character/StateMachine/StateMachine.h"

void ClimbState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Climbing);
}

void ClimbState::End()
{
}
