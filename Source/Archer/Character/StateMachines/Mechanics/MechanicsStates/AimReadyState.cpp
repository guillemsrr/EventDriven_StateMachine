// Copyright (c) Guillem Serra. All Rights Reserved.

#include "AimReadyState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FAimReadyState::Begin()
{
	MechanicsStateMachine->StartAimingDelegate.AddRaw(this, &FAimReadyState::SetAimState);
	MechanicsStateMachine->StartFreeAimDelegate.AddRaw(this, &FAimReadyState::SetFreeAimExpected);
	MechanicsStateMachine->StopFreeAimDelegate.AddRaw(this, &FAimReadyState::SetFreeAimNotExpected);

	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::Movement);
}

void FAimReadyState::End()
{
	MechanicsStateMachine->StartAimingDelegate.Clear();
	MechanicsStateMachine->StartFreeAimDelegate.Clear();
	MechanicsStateMachine->StopFreeAimDelegate.Clear();
}

void FAimReadyState::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(0, -1, FColor::Green, "AimReadyState");
}

void FAimReadyState::SetAimState() const
{
	if (IsFreeAimExpected)
	{
		MechanicsStateMachine->SetFreeAimState();
	}
	else
	{
		MechanicsStateMachine->SetAutoAimState();
	}
}

void FAimReadyState::SetFreeAimExpected()
{
	IsFreeAimExpected = true;
}

void FAimReadyState::SetFreeAimNotExpected()
{
	IsFreeAimExpected = false;
}
