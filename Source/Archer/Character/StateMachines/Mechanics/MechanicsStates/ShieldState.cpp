// Copyright (c) Guillem Serra. All Rights Reserved.

#include "ShieldState.h"

#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FShieldState::Begin()
{
	FMechanicStateBase::Begin();

	MechanicsStateMachine->GetCharacterAnimations()->SetOrientationType(EOrientationType::AimDirection);
}

void FShieldState::End()
{
}

void FShieldState::Tick(float DeltaTime)
{
	CharacterMechanics->InterpolateAimDirection(DeltaTime);
}
