#pragma once
#include "StateBase.h"

class SlowmoState : public StateBase
{
public:
	explicit SlowmoState(FStateMachine* StateMachine)
		: StateBase(StateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
};
