#pragma once
#include "LocomotionStateBase.h"

class FRunState: public FLocomotionStateBase
{
public:
	explicit FRunState(FStateMachineBase* StateMachine)
	: FLocomotionStateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
