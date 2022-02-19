// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "Archer/Player/ArcherPlayerController.h"
#include "ArchTrace.generated.h"

class USlowTimeManager;
class AEnemy;

UCLASS(Blueprintable)
class ARCHER_API UArchTrace : public UActorComponent
{
	GENERATED_BODY()
public:
	UArchTrace();

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

	FORCEINLINE bool IsThereAnyTarget() const {return AutoAimTargets.Num() > 0;}
	FORCEINLINE FRotator GetAimRotator() const { return AimDirection.Rotation(); }
	FORCEINLINE void SetAutoAimTargets(TArray<AEnemy*> Targets) { AutoAimTargets = Targets; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName BowSocketName;

	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AimInterpolationSpeed = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxAimAngle = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAimOneMinimum = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDebugAimLine = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDebugActualAimLine = true;
	
	virtual void BeginPlay() override;

private:
	AActor* Owner;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	FVector AimDirection;
	FVector TargetAimDirection;
	float TargetAimDistance;
	USkeletalMeshSocket const* BowSocket;
	TArray<AEnemy*> AutoAimTargets;
	AArcherPlayerController* PlayerController;
	
	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();

	FVector2D GetPlayerScreenPosition() const;
	void GetPlayerStickPositionAndDirection(float& PlayerScreenLocation, FVector2D& PlayerDirection);
	TArray<AActor*> GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection);
};
