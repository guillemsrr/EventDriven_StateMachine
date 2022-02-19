// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "MechanicStateBase.h"

class FAimReadyState : public FMechanicStateBase
{
public:
	FAimReadyState(FStateMachineBase* MechanicsStateMachine) : FMechanicStateBase(MechanicsStateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool IsFreeAimExpected = false;

	void SetAimState() const;
	void SetFreeAimExpected();
	void SetFreeAimNotExpected();
};
