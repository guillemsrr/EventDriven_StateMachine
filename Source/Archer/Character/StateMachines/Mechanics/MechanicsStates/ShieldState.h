#pragma once
#include "MechanicStateBase.h"

class FShieldState: public FMechanicStateBase
{
public:
	FShieldState(FStateMachineBase* MechanicsStateMachine) : FMechanicStateBase(MechanicsStateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;
};
