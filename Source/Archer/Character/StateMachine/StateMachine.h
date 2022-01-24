#pragma once
#include "Archer/Character/ArcherCharacter.h"

class StateBase;
class AArcherCharacter;
class FCharacterMovement;
class FCharacterMechanics;

DECLARE_MULTICAST_DELEGATE_OneParam(MovementSignature, float);
DECLARE_MULTICAST_DELEGATE(ActionSignature);

class FStateMachine
{
public:
	explicit FStateMachine(AArcherCharacter* ArcherCharacter);
	~FStateMachine();

	StateBase* State;

	MovementSignature MoveForwardDelegate;
	MovementSignature MoveRightDelegate;
	ActionSignature StartRunDelegate;
	ActionSignature StopRunDelegate;
	ActionSignature StartAimDelegate;
	ActionSignature StopAimDelegate;
	ActionSignature StartFreeAimDelegate;
	ActionSignature StopFreeAimDelegate;
	ActionSignature StartShootDelegate;
	ActionSignature ReleaseShootDelegate;
	ActionSignature DashDelegate;
	ActionSignature StartClimbDelegate;
	ActionSignature StopClimbDelegate;

	FDelegateHandle MoveForwardDelegateHandle;
	FDelegateHandle MoveRightDelegateHandle;
	FDelegateHandle StartRunDelegateHandle;
	FDelegateHandle StopRunDelegateHandle;
	FDelegateHandle StartAimDelegateHandle;
	FDelegateHandle StopAimDelegateHandle;

	void SetWalkState();
	void SetRunState();
	void SetDashState();
	void SetJumpState();
	void SetClimbState();
	void SetSlowmoState();

	FORCEINLINE FCharacterMovement* GetCharacterMovement() const { return ArcherCharacter->GetArcherMovement(); }
	FORCEINLINE FCharacterMechanics* GetCharacterMechanics() const { return ArcherCharacter->GetCharacterMechanics(); }

private:
	AArcherCharacter* ArcherCharacter;

	template <class T>
	void SetState();
};
