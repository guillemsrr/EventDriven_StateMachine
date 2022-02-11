﻿#include "AutoAimState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FAutoAimState::Begin()
{
	FMechanicStateBase::Begin();
	MechanicsStateMachine->GetCharacterAnimations()->SetAttackState(ECharacterAttackState::Aiming);
	CharacterMechanics->SetAutoAimTargets();

	MechanicsStateMachine->StartShootingDelegate.AddRaw(this, &FAutoAimState::DrawArrowAndStartPrecisionCount);
	MechanicsStateMachine->StopShootingDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::ReleaseArrow);
	MechanicsStateMachine->StartFreeAimDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetFreeAimState);

	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);
}

void FAutoAimState::End()
{
	CharacterMechanics->StopDrawingArrow();
	MechanicsStateMachine->StartShootingDelegate.Clear();
	MechanicsStateMachine->StopShootingDelegate.Clear();
	MechanicsStateMachine->StartFreeAimDelegate.Clear();
}

void FAutoAimState::Tick(float DeltaTime)
{
	CharacterMechanics->AutoAim();
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
	GEngine->AddOnScreenDebugMessage(0, -1, FColor::Green, "AutoAim");
}

void FAutoAimState::DrawArrowAndStartPrecisionCount()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetPrecisionAimState);
	CharacterMechanics->DrawArrow(TimerDelegate);
}