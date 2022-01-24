#include "WalkState.h"
#include "Archer/Character/ArcherCharacter.h"
#include "Archer/Character/StateMachine/StateMachine.h"
#include "RunState.h"

void WalkState::Begin()
{
	StateMachine->GetCharacterMovement()->SetSpeed(WalkSpeed);

	StateMachine->MoveForwardDelegateHandle = StateMachine->MoveForwardDelegate.AddRaw(
		StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveForward);
	
	StateMachine->MoveRightDelegateHandle = StateMachine->MoveRightDelegate.AddRaw(
		StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveRight);
	
	StateMachine->StartRunDelegateHandle = StateMachine->StartRunDelegate.AddRaw(
		StateMachine, &FStateMachine::SetRunState);
	
	StateMachine->StartAimDelegateHandle = StateMachine->StartAimDelegate.AddRaw(
		StateMachine->GetCharacterMechanics(), &FCharacterMechanics::StartAim);
	
	StateMachine->StopAimDelegateHandle = StateMachine->StopAimDelegate.AddRaw(
		StateMachine->GetCharacterMechanics(), &FCharacterMechanics::StopAim);
}

void WalkState::End()
{
	StateMachine->MoveForwardDelegate.Remove(StateMachine->MoveForwardDelegateHandle);
	StateMachine->MoveRightDelegate.Remove(StateMachine->MoveRightDelegateHandle);
	StateMachine->StartRunDelegate.Remove(StateMachine->StartRunDelegateHandle);
	StateMachine->StartAimDelegate.Remove(StateMachine->StartAimDelegateHandle);
	StateMachine->StopAimDelegate.Remove(StateMachine->StopAimDelegateHandle);
}
