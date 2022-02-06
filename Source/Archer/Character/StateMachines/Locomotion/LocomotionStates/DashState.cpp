#include "DashState.h"

#include "Archer/Character/StateMachine/StateMachine.h"

void DashState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Dashing);
}

void DashState::End()
{
}
