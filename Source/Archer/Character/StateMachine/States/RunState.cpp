#include "RunState.h"
#include "WalkState.h"
#include "Archer/Character/ArcherCharacter.h"
#include "Archer/Character/StateMachine/StateMachine.h"

void RunState::Begin()
{
	StateMachine->GetCharacterMovement()->SetSpeed(750.f);
	StateMachine->GetCharacterMechanics()->StopAim();
	
	StateMachine->MoveForwardDelegateHandle = StateMachine->MoveForwardDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveForward);
	StateMachine->MoveRightDelegateHandle = StateMachine->MoveRightDelegate.AddRaw(StateMachine->GetCharacterMovement(), &FCharacterMovement::MoveRight);
	StateMachine->StopRunDelegateHandle = StateMachine->StopRunDelegate.AddRaw(StateMachine, &FStateMachine::SetWalkState);
}

void RunState::End()
{
	StateMachine->MoveForwardDelegate.Remove(StateMachine->MoveForwardDelegateHandle);
	StateMachine->MoveRightDelegate.Remove(StateMachine->MoveRightDelegateHandle);
	StateMachine->StopRunDelegate.Remove(StateMachine->StopRunDelegateHandle);
}