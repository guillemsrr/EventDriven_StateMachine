// Copyright (c) Guillem Serra. All Rights Reserved.

#include "FreeAimState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"
#include "Archer/Utilities/Debug.h"

void FFreeAimState::Begin()
{
	FMechanicStateBase::Begin();
	MechanicsStateMachine->GetCharacterAnimations()->SetAttackState(ECharacterAttackState::Aiming);

	MechanicsStateMachine->StartShootingDelegate.AddRaw(this, &FFreeAimState::DrawArrowAndStartPrecisionCount);
	MechanicsStateMachine->StopShootingDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::ReleaseArrow);
	MechanicsStateMachine->StopFreeAimDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);

	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);

	if (MechanicsStateMachine->IsPlayerUsingGamepad())
	{
		TickDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::FreeAimGamepad);
	}
	else
	{
		TickDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::FreeAim);
	}
}

void FFreeAimState::End()
{
	CharacterMechanics->StopDrawingArrow();

	MechanicsStateMachine->StartShootingDelegate.Clear();
	MechanicsStateMachine->StopShootingDelegate.Clear();
	MechanicsStateMachine->StopFreeAimDelegate.Clear();
}

void FFreeAimState::Tick(float DeltaTime)
{
	TickDelegate.Broadcast();
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
	DEBUG_LOG_TICK("Free Aim");
}

void FFreeAimState::DrawArrowAndStartPrecisionCount()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetPrecisionAimState);
	CharacterMechanics->DrawArrow(TimerDelegate);
}
