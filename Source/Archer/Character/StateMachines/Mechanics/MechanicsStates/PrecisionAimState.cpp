#include "PrecisionAimState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/Movement/CharacterMovement.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"
#include "Archer/Utilities/Debug.h"

void FPrecisionAimState::Begin()
{
	FMechanicStateBase::Begin();

	MechanicsStateMachine->StopShootingDelegate.AddRaw(this, &FPrecisionAimState::ReleaseAndSetAutoAimState);
	//MechanicsStateMachine->StopShootingDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::ReleaseArrow);
	//MechanicsStateMachine->StopShootingDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);
	MechanicsStateMachine->StopFreeAimDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);
	MechanicsStateMachine->AimXValueDelegate.AddRaw(this, &FPrecisionAimState::SetPrecisionXOffset);
	MechanicsStateMachine->AimYValueDelegate.AddRaw(this, &FPrecisionAimState::SetPrecisionYOffset);

	if(MechanicsStateMachine->IsPlayerUsingGamepad())
	{
		TargetActor = CharacterMechanics->GetMouseClosestTarget();
	}
	else
	{
		TargetActor = CharacterMechanics->GetGamepadClosestTarget();
	}
	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);
}

void FPrecisionAimState::Tick(float DeltaTime)
{
	DEBUG_LOG_TICK("PrecisionAimState");

	if(Offset.Size()>1000.f)
	{
		Offset = FVector(0);
	}

	CharacterMechanics->PrecisionAim(TargetActor->GetActorLocation() + Offset);
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
}

void FPrecisionAimState::SetPrecisionXOffset(float Value)
{
	DEBUG_LOG_NUMBER_TICK("X offset ", Value);
	
	FVector RightVector = MechanicsStateMachine->GetCharacterMovement()->GetCameraRelativeRightVector();
	RightVector*=Value*OffsetInputRelation;
	Offset += RightVector;
}

void FPrecisionAimState::SetPrecisionYOffset(float Value)
{
	DEBUG_LOG_NUMBER_TICK("Y offset ", Value);

	FVector ForwardVector = MechanicsStateMachine->GetCharacterMovement()->GetCameraRelativeForwardVector();
	ForwardVector*=Value*OffsetInputRelation;
	Offset+=ForwardVector;
}

void FPrecisionAimState::ReleaseAndSetAutoAimState() const
{
	CharacterMechanics->ReleaseArrow();
	MechanicsStateMachine->SetAutoAimState();
}

void FPrecisionAimState::End()
{
	MechanicsStateMachine->StopShootingDelegate.Clear();
	MechanicsStateMachine->StopShootingDelegate.Clear();
	MechanicsStateMachine->AimXValueDelegate.Clear();
	MechanicsStateMachine->AimYValueDelegate.Clear();
}
