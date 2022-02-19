// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "Archer/Character/StateMachines/StateMachineBase.h"

class FMechanicsStateMachine: public FStateMachineBase
{
public:
	explicit FMechanicsStateMachine(AArcherCharacter* ArcherCharacter);

	ActionSignature StartAimingDelegate;
	ActionSignature StopAimingDelegate;
	ActionSignature StartShootingDelegate;
	ActionSignature StopShootingDelegate;
	ActionSignature StartFreeAimDelegate;
	ActionSignature StopFreeAimDelegate;

	MovementSignature AimXValueDelegate;
	MovementSignature AimYValueDelegate;
	
	void Tick(float DeltaTime);
	
	void SetEmptyState();
	void SetAimReadyState();
	void SetFreeAimState();
	void SetAutoAimState();
	void SetPrecisionAimState();
	
protected:
	virtual void SetSpecificState() override;

private:
	class FMechanicStateBase* MechanicState;
};
