#include "LocomotionStateMachine.h"

#include "Archer/Character/ArcherCharacter.h"
#include "LocomotionStates/ClimbState.h"
#include "LocomotionStates/DashState.h"
#include "LocomotionStates/JumpState.h"
#include "LocomotionStates/RunState.h"
#include "LocomotionStates/SlowmoState.h"
#include "LocomotionStates/WalkState.h"

FLocomotionStateMachine::FLocomotionStateMachine(AArcherCharacter* ArcherCharacter) : FStateMachineBase(ArcherCharacter)
{
	this->ArcherCharacter = ArcherCharacter;
	State = new FWalkState(this);
}

FLocomotionStateMachine::~FLocomotionStateMachine()
{
	delete State;
}

void FLocomotionStateMachine::SetWalkState()
{
	SetState<FWalkState>();
}

void FLocomotionStateMachine::SetRunState()
{
	SetState<FRunState>();
}

void FLocomotionStateMachine::SetDashState()
{
	SetState<FDashState>();
}

void FLocomotionStateMachine::SetJumpState()
{
	SetState<FJumpState>();
}

void FLocomotionStateMachine::SetClimbState()
{
	SetState<FClimbState>();
}

void FLocomotionStateMachine::SetSlowmoState()
{
	SetState<FSlowmoState>();
}

FMechanicsStateMachine* FLocomotionStateMachine::GetMechanicsStateMachine() const
{
	return ArcherCharacter->GetMechanicsStateMachine(); 
}
