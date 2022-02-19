// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "LocomotionStateBase.h"

class FWalkState: public FLocomotionStateBase
{
public:
	explicit FWalkState(FStateMachineBase* StateMachine) : FLocomotionStateBase(StateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
};
