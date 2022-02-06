#include "StateMachine.h"
#include "Archer/Character/ArcherCharacter.h"
#include "States/ClimbState.h"
#include "States/DashState.h"
#include "States/JumpState.h"
#include "States/RunState.h"
#include "States/SlowmoState.h"
#include "States/StateBase.h"
#include "States/WalkState.h"

FLocomotionStateMachine::FLocomotionStateMachine(AArcherCharacter* ArcherCharacter)
{
	this->ArcherCharacter = ArcherCharacter;
	State = new WalkState(this);
}

FLocomotionStateMachine::~FLocomotionStateMachine()
{
	delete State;
}

template <class T>
void FLocomotionStateMachine::SetState()
{
	State->End();
	delete State;
	State = new T(this);
	State->Begin();
}

void FLocomotionStateMachine::SetWalkState()
{
	SetState<WalkState>();
}

void FLocomotionStateMachine::SetRunState()
{
	SetState<RunState>();
}

void FLocomotionStateMachine::SetDashState()
{
	SetState<DashState>();
}

void FLocomotionStateMachine::SetJumpState()
{
	SetState<JumpState>();
}

void FLocomotionStateMachine::SetClimbState()
{
	SetState<ClimbState>();
}

void FLocomotionStateMachine::SetSlowmoState()
{
	SetState<SlowmoState>();
}
