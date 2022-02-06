#include "MechanicsStateMachine.h"

#include "MechanicsStates/AimReadyState.h"
#include "MechanicsStates/AutoAimState.h"
#include "MechanicsStates/EmptyState.h"
#include "MechanicsStates/FreeAimState.h"
#include "MechanicsStates/PrecisionAimState.h"

FMechanicsStateMachine::FMechanicsStateMachine(AArcherCharacter* ArcherCharacter) : FStateMachineBase(ArcherCharacter)
{
	State = new FAimReadyState(this);
	FMechanicsStateMachine::SetSpecificState();
}

void FMechanicsStateMachine::Tick(float DeltaTime)
{
	MechanicState->Tick(DeltaTime);
}

void FMechanicsStateMachine::SetEmptyState()
{
	SetState<FEmptyState>();
	SetSpecificState();
}

void FMechanicsStateMachine::SetAimReadyState()
{
	SetState<FAimReadyState>();
	SetSpecificState();
}

void FMechanicsStateMachine::SetFreeAimState()
{
	SetState<FFreeAimState>();
	SetSpecificState();
}

void FMechanicsStateMachine::SetAutoAimState()
{
	SetState<FAutoAimState>();
	SetSpecificState();
}

void FMechanicsStateMachine::SetPrecisionAimState()
{
	SetState<FPrecisionAimState>();
	SetSpecificState();
}

void FMechanicsStateMachine::SetSpecificState()
{
	MechanicState = static_cast<FMechanicStateBase*>(State);
}