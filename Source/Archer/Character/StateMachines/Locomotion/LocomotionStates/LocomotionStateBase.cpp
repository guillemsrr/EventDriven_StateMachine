// Copyright (c) Guillem Serra. All Rights Reserved.

#include "LocomotionStateBase.h"

FLocomotionStateBase::FLocomotionStateBase(FStateMachineBase* StateMachine)
{
	this->StateMachine = (FLocomotionStateMachine*)(StateMachine);
}