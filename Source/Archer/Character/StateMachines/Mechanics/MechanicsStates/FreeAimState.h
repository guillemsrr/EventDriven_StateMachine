#pragma once
#include "MechanicStateBase.h"

class FFreeAimState: public FMechanicStateBase
{
public:
	FFreeAimState(FStateMachineBase* MechanicsStateMachine) : FMechanicStateBase(MechanicsStateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;

private:
	void DrawArrowAndStartPrecisionCount();
};
