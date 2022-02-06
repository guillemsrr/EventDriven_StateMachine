#pragma once
#include "LocomotionStateBase.h"


class FJumpState: public FLocomotionStateBase
{
public:
	explicit FJumpState(FStateMachineBase* StateMachine)
	: FLocomotionStateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
