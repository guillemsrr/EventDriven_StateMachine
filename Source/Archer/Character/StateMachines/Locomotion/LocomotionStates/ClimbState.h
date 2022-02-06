#pragma once
#include "LocomotionStateBase.h"

class FClimbState: public FLocomotionStateBase
{
public:
	explicit FClimbState(FStateMachineBase* StateMachine)
	: FLocomotionStateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
