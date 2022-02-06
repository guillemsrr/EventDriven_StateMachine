#pragma once
#include "StateBase.h"

class DashState : public StateBase
{
public:
	explicit DashState(FStateMachine* StateMachine)
		: StateBase(StateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
};
