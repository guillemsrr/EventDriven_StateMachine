#pragma once
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"

class LocomotionStateBase
{
public:
	LocomotionStateBase(FLocomotionStateMachine* StateMachine);
	virtual ~LocomotionStateBase(){};

	virtual void Begin() = 0;
	virtual void End() = 0;

protected:
	FLocomotionStateMachine* StateMachine;
};
