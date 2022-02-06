#pragma once
#include "LocomotionStateBase.h"

class FSlowmoState : public FLocomotionStateBase
{
public:
	explicit FSlowmoState(FStateMachineBase* StateMachine)
		: FLocomotionStateBase(StateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
};
