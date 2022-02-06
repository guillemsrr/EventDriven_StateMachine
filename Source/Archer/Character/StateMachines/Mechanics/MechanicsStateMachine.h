#pragma once
#include "Archer/Character/StateMachines/StateMachineBase.h"

class FMechanicsStateMachine: public FStateMachineBase
{
public:
	explicit FMechanicsStateMachine(AArcherCharacter* ArcherCharacter);

	void Tick(float DeltaTime);
	
	void SetEmptyState();
	void SetAimReadyState();
	void SetFreeAimState();
	void SetAutoAimState();
	void SetPrecisionAimState();

	ActionSignature StartAimingDelegate;
	ActionSignature StopAimingDelegate;
	ActionSignature StartShootingDelegate;
	ActionSignature StopShootingDelegate;
	ActionSignature StartFreeAimDelegate;
	ActionSignature StopFreeAimDelegate;
	MovementSignature PrecisionXDelegate;
	MovementSignature PrecisionYDelegate;
	
protected:
	virtual void SetSpecificState() override;

private:
	class FMechanicStateBase* MechanicState;
};
