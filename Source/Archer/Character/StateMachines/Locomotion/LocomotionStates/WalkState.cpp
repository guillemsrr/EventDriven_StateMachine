#include "WalkState.h"
#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Character/Animation/CharacterAnimationStates.h"
#include "Archer/Character/Movement/CharacterMovement.h"
#include "Archer/Character/StateMachines/Locomotion/LocomotionStateMachine.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

void FWalkState::Begin()
{
	StateMachine->GetCharacterAnimations()->SetLocomotionState(ECharacterLocomotionState::Normal);
	StateMachine->GetCharacterMovement()->SetWalkSpeed();
	StateMachine->GetMechanicsStateMachine()->SetAimReadyState();

	StateMachine->MoveForwardDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveForward);
	StateMachine->MoveRightDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveRight);
	StateMachine->StartRunDelegate.AddRaw(StateMachine, &FLocomotionStateMachine::SetRunState);

	StateMachine->GetMechanicsStateMachine()->StopAimingDelegate.AddRaw(StateMachine->GetMechanicsStateMachine(),
	                                                                    &FMechanicsStateMachine::SetAimReadyState);
}

void FWalkState::End()
{
	StateMachine->MoveForwardDelegate.Clear();
	StateMachine->MoveRightDelegate.Clear();
	StateMachine->StartRunDelegate.Clear();

	StateMachine->GetMechanicsStateMachine()->StopAimingDelegate.Clear();
}
