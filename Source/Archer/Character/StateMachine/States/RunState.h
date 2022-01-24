#pragma once
#include "StateBase.h"

class RunState: public StateBase
{
public:
	explicit RunState(FStateMachine* StateMachine)
	: StateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
