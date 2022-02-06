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
	AActor* ClosestTarget = GetClosestTarget();
	if (!ClosestTarget) return;
	ArchTrace->SetAimDirection(ClosestTarget);
}

void FCharacterMechanics::FreeAim() const
{
	ArchTrace->FreeAim();
}

void FCharacterMechanics::PrecisionAim(const FVector TargetLocation) const
{
	ArchTrace->SetAimDirection(TargetLocation);
}

void FCharacterMechanics::InterpolateAimDirection(float DeltaTime) const
{
	ArchTrace->SetInterpolatedAimDirection(DeltaTime);
}

AActor* FCharacterMechanics::GetClosestTarget() const
{
	return ArchTrace->GetClosestTarget();
}

void FCharacterMechanics::SetAutoAimTargets() const
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(ArchTrace->GetWorld(), AEnemy::StaticClass(), Enemies);
	ArchTrace->SetAutoAimTargets(Enemies);
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
	//after some timer, it should go back to aiming/ normal
}

void FCharacterMechanics::StopDrawingArrow()
{
	ArchTrace->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
}