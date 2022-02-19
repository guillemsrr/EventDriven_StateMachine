// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "MechanicStateBase.h"

class FEmptyState: public FMechanicStateBase
{
public:
	explicit FEmptyState(FStateMachineBase* MechanicsStateMachine)
		: FMechanicStateBase(MechanicsStateMachine)
	{
	}

	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;
};
