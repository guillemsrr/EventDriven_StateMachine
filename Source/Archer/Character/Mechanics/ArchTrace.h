#pragma once
#include "Archer/Player/ArcherPlayerController.h"
#include "ArchTrace.generated.h"

class USlowTimeManager;

UCLASS()
class ARCHER_API UArchTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	UArchTrace();

	void Initialize(USlowTimeManager* TimeManager);
	void SetInterpolatedAimDirection(float DeltaTime);
	void SetBowSocket(USkeletalMeshComponent* skeletalMeshComponent);
	void FreeAim();
	void SetAimDirection(const AActor* ClosestTarget);
	void SetAimDirectionToTargetPosition(const FVector TargetLocation);
	void Shoot(TSubclassOf<class AProjectile> Projectile);
	void GetMouseLocationAndDirection(FVector& WorldLocation, FVector& WorldDirection);
	AActor* GetMouseClosestTarget();
	AActor* GetGamepadClosestTarget();
	FVector2D GetActorScreenLocation(AActor* Target);

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
	AArcherPlayerController* PlayerController;
	const float MAX_AIM_ANGLE = 5.f;
	
	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();

	FVector2D GetPlayerScreenPosition() const;
	void GetPlayerStickPositionAndDirection(float& PlayerScreenLocation, FVector2D& PlayerDirection);
	TArray<AActor*> GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection);
};
