// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "LocomotionStateBase.h"

class FDashState : public FLocomotionStateBase
{
public:
	explicit FDashState(FStateMachineBase* StateMachine)
		: FLocomotionStateBase(StateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
};
