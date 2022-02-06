#include "MechanicStateBase.h"

#include "Archer/Character/Mechanics/CharacterMechanics.h"
#include "Archer/Character/StateMachines/Mechanics/MechanicsStateMachine.h"

FMechanicStateBase::FMechanicStateBase(FStateMachineBase* MechanicsStateMachine) : FStateBase()
{
	this->MechanicsStateMachine = static_cast<FMechanicsStateMachine*>(MechanicsStateMachine);
}

/*FMechanicStateBase::~FMechanicStateBase()
{
	delete MechanicsStateMachine;
	delete CharacterMechanics;
}*/

//TODO -> no podia posar-ho al constructor?
void FMechanicStateBase::Begin()
{
	CharacterMechanics = MechanicsStateMachine->GetCharacterMechanics();
}
