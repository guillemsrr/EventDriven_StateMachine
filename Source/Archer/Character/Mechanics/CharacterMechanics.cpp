#include "CharacterMechanics.h"

#include "ArchTrace.h"
#include "Archer/Character/Animation/CharacterAnimations.h"
#include "Archer/Enemies/Enemy.h"
#include "Kismet/GameplayStatics.h"

FCharacterMechanics::FCharacterMechanics(UArchTrace* ArchTrace, UCharacterAnimations* characterAnimations)
{
	this->ArchTrace = ArchTrace;
	this->CharacterAnimations = characterAnimations;
}

void FCharacterMechanics::AutoAim()
{
	AActor* ClosestTarget = GetMouseClosestTarget();
	
	if (!ClosestTarget) return;
	
	ArchTrace->SetAimDirection(ClosestTarget);
}

void FCharacterMechanics::AutoAimGamepad()
{
	AActor* ClosestTarget = GetGamepadClosestTarget();
	
	if (!ClosestTarget) return;
	
	ArchTrace->SetAimDirection(ClosestTarget);
}

void FCharacterMechanics::FreeAim() const
{
	ArchTrace->FreeAim();
}

void FCharacterMechanics::FreeAimGamepad() const
{
	ArchTrace->FreeAim();
}

void FCharacterMechanics::PrecisionAim(const FVector TargetLocation) const
{
	ArchTrace->SetAimDirectionToTargetPosition(TargetLocation);
}

void FCharacterMechanics::InterpolateAimDirection(float DeltaTime) const
{
	ArchTrace->SetInterpolatedAimDirection(DeltaTime);
}

AActor* FCharacterMechanics::GetMouseClosestTarget() const
{
	return ArchTrace->GetMouseClosestTarget();
}

AActor* FCharacterMechanics::GetGamepadClosestTarget() const
{
	return ArchTrace->GetGamepadClosestTarget();
}

void FCharacterMechanics::SetAutoAimTargets() const
{
	TArray<AActor*> EnemyActors;
	TArray<AEnemy*> AliveEnemies;
	UGameplayStatics::GetAllActorsOfClass(ArchTrace->GetWorld(), AEnemy::StaticClass(), EnemyActors);
	
	for (int EnemyIndex = EnemyActors.Num() - 1; EnemyIndex >= 0; EnemyIndex--)
	{
		AEnemy* Enemy = Cast<AEnemy, AActor>(EnemyActors[EnemyIndex]);
		if(Enemy->IsAlive())
		{
			AliveEnemies.Add(Enemy);
		}
	}
	ArchTrace->SetAutoAimTargets(AliveEnemies);
}

bool FCharacterMechanics::IsThereAnyTarget() const
{
	return ArchTrace->IsThereAnyTarget();
}

void FCharacterMechanics::DrawArrow(FTimerDelegate TimerDelegate)
{
	ArchTrace->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, HoldShootForPrecisionModeTime, false);
	
	CharacterAnimations->SetAttackState(ECharacterAttackState::Drawback);
}

void FCharacterMechanics::ReleaseArrow()
{
	StopDrawingArrow();
	CharacterAnimations->SetAttackState(ECharacterAttackState::Release);
	ArchTrace->Shoot(ProjectileClass);
	
	//TODO after some timer, it should go back to aiming/ normal
}

void FCharacterMechanics::StopDrawingArrow()
{
	ArchTrace->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
}