#pragma once
#include "Archer/Character/StateMachines/StateBase.h"

class FMechanicsStateMachine;

class FMechanicStateBase: public FStateBase
{
public:
	explicit FMechanicStateBase(class FStateMachineBase* MechanicsStateMachine);
	//virtual ~FMechanicStateBase() override;

	virtual void Begin() override;
	virtual void Tick(float DeltaTime) = 0;

protected:
	FMechanicsStateMachine* MechanicsStateMachine;
	class FCharacterMechanics* CharacterMechanics;
};
