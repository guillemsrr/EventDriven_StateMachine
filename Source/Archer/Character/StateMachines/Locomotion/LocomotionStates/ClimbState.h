#pragma once
#include "StateBase.h"

class ClimbState: public StateBase
{
public:
	explicit ClimbState(FStateMachine* StateMachine)
	: StateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
