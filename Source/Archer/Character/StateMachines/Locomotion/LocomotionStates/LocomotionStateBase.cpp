#include "LocomotionStateBase.h"

FLocomotionStateBase::FLocomotionStateBase(FStateMachineBase* StateMachine)
{
	this->StateMachine = reinterpret_cast<FLocomotionStateMachine*>(StateMachine);
}