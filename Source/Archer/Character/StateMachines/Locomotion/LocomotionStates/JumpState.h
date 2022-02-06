#pragma once

#include "StateBase.h"

class JumpState: public StateBase
{
public:
	explicit JumpState(FStateMachine* StateMachine)
	: StateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
