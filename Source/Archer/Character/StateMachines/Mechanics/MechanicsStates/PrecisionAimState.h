// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "MechanicStateBase.h"

class FPrecisionAimState: public FMechanicStateBase
{
public:
	FPrecisionAimState(FStateMachineBase* MechanicsStateMachine) : FMechanicStateBase(MechanicsStateMachine)
	{
	}
	
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick(float DeltaTime) override;
	

private:
	AActor* TargetActor;
	FVector Offset;

	const float OffsetInputRelation = 5.f;

	void SetPrecisionXOffset(float Value);
	void SetPrecisionYOffset(float Value);
	void ReleaseAndSetAutoAimState() const;
};
