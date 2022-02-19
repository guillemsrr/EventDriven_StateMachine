// Copyright (c) Guillem Serra. All Rights Reserved.

#include "RunState.h"
#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Movement/CharacterMovement.h"
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FRunState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Running);
	StateMachine->GetCharacterMovement()->SetRunSpeed();
	StateMachine->GetMechanicsStateMachine()->SetEmptyState();
	
	StateMachine->MoveForwardDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveForward);
	StateMachine->MoveRightDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveRight);
	StateMachine->StopRunDelegate.AddRaw(StateMachine, &FLocomotionStateMachine::SetWalkState);
}

void FRunState::End()
{
	StateMachine->MoveForwardDelegate.Clear();
	StateMachine->MoveRightDelegate.Clear();
	StateMachine->StopRunDelegate.Clear();
}