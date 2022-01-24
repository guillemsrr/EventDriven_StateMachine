#include "StateMachine.h"
#include "Archer/Character/ArcherCharacter.h"
#include "States/ClimbState.h"
#include "States/DashState.h"
#include "States/JumpState.h"
#include "States/RunState.h"
#include "States/SlowmoState.h"
#include "States/StateBase.h"
#include "States/WalkState.h"

FStateMachine::FStateMachine(AArcherCharacter* ArcherCharacter)
{
	this->ArcherCharacter = ArcherCharacter;
	State = new WalkState(this);
}

FStateMachine::~FStateMachine()
{
	delete State;
}

template <class T>
void FStateMachine::SetState()
{
	State->End();
	delete State;
	State = new T(this);
	State->Begin();
}

void FStateMachine::SetWalkState()
{
	SetState<WalkState>();
}

void FStateMachine::SetRunState()
{
	SetState<RunState>();
}

void FStateMachine::SetDashState()
{
	SetState<DashState>();
}

void FStateMachine::SetJumpState()
{
	SetState<JumpState>();
}

void FStateMachine::SetClimbState()
{
	SetState<ClimbState>();
}

void FStateMachine::SetSlowmoState()
{
	SetState<SlowmoState>();
}
