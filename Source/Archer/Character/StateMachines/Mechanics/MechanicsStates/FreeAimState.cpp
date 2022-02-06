#include "FreeAimState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FFreeAimState::Begin()
{
	FMechanicStateBase::Begin();
	MechanicsStateMachine->GetCharacterAnimations()->SetAttackState(ECharacterAttackState::Aiming);

	MechanicsStateMachine->StartShootingDelegate.AddRaw(this, &FFreeAimState::DrawArrowAndStartPrecisionCount);
	MechanicsStateMachine->StopShootingDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::ReleaseArrow);
	MechanicsStateMachine->StopFreeAimDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);

	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);
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
	CharacterMechanics->FreeAim();
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
	GEngine->AddOnScreenDebugMessage(0, -1, FColor::Green, "Free Aim");
}

void FFreeAimState::DrawArrowAndStartPrecisionCount()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetPrecisionAimState);
	CharacterMechanics->DrawArrow(TimerDelegate);
}
