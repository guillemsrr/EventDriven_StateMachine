#pragma once
#include "ArchTrace.generated.h"

class USlowTimeManager;

UCLASS()
class ARCHER_API UArchTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	UArchTrace();

	virtual void InitializeComponent() override;
	void Initialize(USlowTimeManager* TimeManager);
	void SetInterpolatedAimDirection(float DeltaTime);
	void SetBowSocket(USkeletalMeshComponent* skeletalMeshComponent);
	void FreeAim();
	void SetAimDirection(const AActor* ClosestTarget);
	void SetAimDirection(const FVector TargetLocation);
	void Shoot(TSubclassOf<class AProjectile> Projectile);
	void GetMouseLocationAndDirection(FVector& WorldLocation, FVector& WorldDirection);
	AActor* GetClosestTarget();

	FORCEINLINE FRotator GetAimRotator() const { return AimDirection.Rotation(); }
	FORCEINLINE void SetAutoAimTargets(TArray<AActor*> Targets) { AutoAimTargets = Targets; }

protected:
	UPROPERTY(EditDefaultsOnly)
	FName BowSocketName;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float AimInterpolationSpeed = 5.f;
	
	virtual void BeginPlay() override;

private:
	AActor* Owner;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	FVector AimDirection;
	FVector TargetAimDirection;
	USkeletalMeshSocket const* BowSocket;
	TArray<AActor*> AutoAimTargets;
	
	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();

	void GetPlayerMousePositionAndDirection(FVector2D& PlayerScreenLocation, FVector2D& PlayerDirection);
	AActor* GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection);
};
