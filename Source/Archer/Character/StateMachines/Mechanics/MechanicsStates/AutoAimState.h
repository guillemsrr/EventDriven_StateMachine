#pragma once
#include "MechanicStateBase.h"

class FAutoAimState: public FMechanicStateBase
{
public:
	FAutoAimState(FStateMachineBase* MechanicsStateMachine) : FMechanicStateBase(MechanicsStateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;

private:
	void DrawArrowAndStartPrecisionCount();
};
