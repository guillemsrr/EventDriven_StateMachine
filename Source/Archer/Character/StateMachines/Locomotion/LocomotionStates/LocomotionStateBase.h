#pragma once
#include "Archer/Character/StateMachines/StateBase.h"

class FLocomotionStateMachine;

class FLocomotionStateBase: public FStateBase
{
public:
	explicit FLocomotionStateBase(class FStateMachineBase* StateMachine);

protected:
	FLocomotionStateMachine* StateMachine;
};
