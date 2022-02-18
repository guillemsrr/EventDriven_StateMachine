#include "LocomotionStateBase.h"

FLocomotionStateBase::FLocomotionStateBase(FStateMachineBase* StateMachine)
{
	this->StateMachine = (FLocomotionStateMachine*)(StateMachine);
}