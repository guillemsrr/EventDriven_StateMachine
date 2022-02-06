#pragma once
#include "StateBase.h"

class AArcherCharacter;
class FCharacterMovement;
class FCharacterMechanics;
class UCharacterAnimations;

DECLARE_MULTICAST_DELEGATE_OneParam(MovementSignature, float);
DECLARE_MULTICAST_DELEGATE(ActionSignature);

class FStateMachineBase
{
public:
	FStateMachineBase(AArcherCharacter* ArcherCharacter);
	virtual ~FStateMachineBase() = default;
	FStateBase* State;

	FCharacterMovement* GetCharacterMovement() const;
	FCharacterMechanics* GetCharacterMechanics() const;
	UCharacterAnimations* GetCharacterAnimations() const;
	UWorld* GetWorld() const;

protected:
	AArcherCharacter* ArcherCharacter;
	
	template <class T>
	void SetState()
	{
		State->End();
		delete State;
		State = new T(this);
		State->Begin();
		SetSpecificState();
	}

	virtual void SetSpecificState() = 0;
};