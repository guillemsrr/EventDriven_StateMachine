// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "MechanicStateBase.h"

#include "Archer/Character/StateMachines/StateMachineBase.h"

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
	ActionSignature TickDelegate;

	void DrawArrowAndStartPrecisionCount();
};
