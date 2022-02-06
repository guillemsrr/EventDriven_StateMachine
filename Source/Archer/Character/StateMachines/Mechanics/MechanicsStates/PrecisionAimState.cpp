#include "PrecisionAimState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/Movement/CharacterMovement.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FPrecisionAimState::Begin()
{
	FMechanicStateBase::Begin();

	MechanicsStateMachine->StopShootingDelegate.AddRaw(this, &FPrecisionAimState::ReleaseAndSetAutoAimState);
	//MechanicsStateMachine->StopShootingDelegate.AddRaw(CharacterMechanics, &FCharacterMechanics::ReleaseArrow);
	//MechanicsStateMachine->StopShootingDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);
	MechanicsStateMachine->StopFreeAimDelegate.AddRaw(MechanicsStateMachine, &FMechanicsStateMachine::SetAutoAimState);
	MechanicsStateMachine->PrecisionXDelegate.AddRaw(this, &FPrecisionAimState::SetPrecisionXOffset);
	MechanicsStateMachine->PrecisionYDelegate.AddRaw(this, &FPrecisionAimState::SetPrecisionYOffset);

	TargetActor = CharacterMechanics->GetClosestTarget();
	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);
}

void FPrecisionAimState::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, "PrecisionAimState");

	if(Offset.Size()>1000.f)
	{
		Offset = FVector();
	}
	
	CharacterMechanics->PrecisionAim(TargetActor->GetActorLocation() + Offset);
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
}

void FPrecisionAimState::SetPrecisionXOffset(float Value)
{
	FVector RightVector = MechanicsStateMachine->GetCharacterMovement()->GetCameraRelativeRightVector();
	RightVector*=Value*OffsetInputRelation;
	Offset += RightVector;
}

void FPrecisionAimState::SetPrecisionYOffset(float Value)
{
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
	MechanicsStateMachine->PrecisionXDelegate.Clear();
	MechanicsStateMachine->PrecisionYDelegate.Clear();
}
