#include "DashState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"

void FDashState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Dashing);
}

void FDashState::End()
{
}
