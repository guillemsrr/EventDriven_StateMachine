#pragma once
#include "Archer/Character/StateMachines/StateMachineBase.h"

class FLocomotionStateMachine: public FStateMachineBase
{
public:
	explicit FLocomotionStateMachine(AArcherCharacter* ArcherCharacter);
	~FLocomotionStateMachine();
	
	MovementSignature MoveForwardDelegate;
	MovementSignature MoveRightDelegate;
	ActionSignature StartRunDelegate;
	ActionSignature StopRunDelegate;
	ActionSignature StartFreeAimDelegate;
	ActionSignature StopFreeAimDelegate;
	ActionSignature DashDelegate;
	ActionSignature StartClimbDelegate;
	ActionSignature StopClimbDelegate;

	void SetWalkState();
	void SetRunState();
	void SetDashState();
	void SetJumpState();
	void SetClimbState();
	void SetSlowmoState();

	class FMechanicsStateMachine* GetMechanicsStateMachine() const;
	
protected:
	virtual void SetSpecificState() override{};
};
