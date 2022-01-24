#include "StateBase.h"
#include "Archer/Character/StateMachine/StateMachine.h"

StateBase::StateBase(FStateMachine* StateMachine)
{
	this->StateMachine = StateMachine;
}
