#pragma once
#include "Archer/Weapons/Projectile.h"
#include "ArchTrace.generated.h"

UCLASS()
class ARCHER_API UArchTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	UArchTrace();
	void Aim();
	void Shoot(TSubclassOf<class AProjectile> Projectile);
	void StopAiming();

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
	void StartLineTraceTimer();
	void LineTraceObjects();
	void LineTraceCoroutine();
	FTimerHandle AimTimerHandle;
};
