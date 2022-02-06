#pragma once

#include "Archer/Weapons/Projectile.h"

class UArchTrace;
class UCharacterAnimations;

class FCharacterMechanics
{
public:
	FCharacterMechanics(UArchTrace* ArchTrace, UCharacterAnimations* characterAnimations);

	void AutoAim();
	void SetAutoAimTargets() const;
	void FreeAim() const;
	void PrecisionAim(const FVector TargetLocation) const;
	AActor* GetClosestTarget() const;
	void DrawArrow(FTimerDelegate TimerDelegate);
	void ReleaseArrow();
	void StopDrawingArrow();
	void InterpolateAimDirection(float DeltaTime) const;
	
	FORCEINLINE void SetProjectile(	TSubclassOf<AProjectile> projectileClass){this->ProjectileClass = projectileClass;}

private:
	UArchTrace* ArchTrace;
	TSubclassOf<AProjectile> ProjectileClass;
	UCharacterAnimations* CharacterAnimations;

	FTimerHandle TimerHandle;
	float HoldShootForPrecisionModeTime = 0.25f;
};
