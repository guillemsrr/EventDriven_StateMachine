#pragma once
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
	void GetMouseLocationAndDirection(FVector& WorldLocation, FVector& WorldDirection);
	void StopAiming();
	virtual void InitializeComponent() override;
	void Initialize(USlowTimeManager* TimeManager);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void SetFreeAim();
	void SetAutoAim();
	void SetBowSocket(USkeletalMeshComponent* skeletalMeshComponent);

	FORCEINLINE FRotator GetAimRotator() { return AimDirection.Rotation(); }
	FORCEINLINE void SetAutoAimTargets(TArray<AActor*> Targets) { AutoAimTargets = Targets; }
	FORCEINLINE bool GetIsFreeAiming(){return IsFreeAiming;}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FName BowSocketName;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

private:
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	bool IsAiming;
	bool IsFreeAiming;
	FVector AimDirection;
	USkeletalMeshSocket const* BowSocket;
	AActor* Owner;

	FTimerHandle AimTimerHandle;
	TArray<AActor*> AutoAimTargets;

	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();
	void FreeAim();
	void AutoAim();
};
