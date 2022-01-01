#pragma once
#include "Archer/General/ArcherGameMode.h"
#include "Archer/Weapons/Projectile.h"
#include "ArchTrace.generated.h"

class USlowTimeManager;

UCLASS()
class ARCHER_API UArchTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	UArchTrace();
	void Aim();
	void Shoot(TSubclassOf<class AProjectile> Projectile);
	void StopAiming();
	virtual void InitializeComponent() override;
	void Initialize(USlowTimeManager* TimeManager);
	void Tick();

protected:
	virtual void BeginPlay() override;

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

private:
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	bool IsAiming;
	FVector AimDirection;

	UPROPERTY()
	AActor* Owner;

	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();
	void LineTraceObjects();
	FTimerHandle AimTimerHandle;
};
