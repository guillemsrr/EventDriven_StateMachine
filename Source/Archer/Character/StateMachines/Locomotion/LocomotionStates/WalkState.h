#pragma once
#include "StateBase.h"

class WalkState: public StateBase
{
public:
	explicit WalkState(FStateMachine* StateMachine)
		: StateBase(StateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
};
