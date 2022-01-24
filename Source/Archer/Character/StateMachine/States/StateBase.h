#pragma once

class FStateMachine;

class StateBase
{
public:
	StateBase(FStateMachine* StateMachine);
	virtual ~StateBase(){};

	virtual void Begin() = 0;
	virtual void End() = 0;

protected:
	FStateMachine* StateMachine;
};
