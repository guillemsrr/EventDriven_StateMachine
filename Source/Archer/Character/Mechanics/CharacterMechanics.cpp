#include "CharacterMechanics.h"

#include "Archer/Enemies/Enemy.h"

#include "Kismet/GameplayStatics.h"

FCharacterMechanics::FCharacterMechanics(UArchTrace* ArchTrace)
{
	this->ArchTrace = ArchTrace;
}

void FCharacterMechanics::StartAim()
{
	if(!ArchTrace->GetIsFreeAiming())
	{
		//TODO-> Get enemies from a global controller
		TArray<AActor*> Enemies;
		UGameplayStatics::GetAllActorsOfClass(ArchTrace->GetWorld(), AEnemy::StaticClass(), Enemies);
		ArchTrace->SetAutoAimTargets(Enemies);
	}
	ArchTrace->Aim();
}

void FCharacterMechanics::StopAim()
{
	ArchTrace->StopAiming();
}
