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
	void SetAimDirection(const AActor* ClosestTarget);
	void SetAimDirectionToTargetPosition(const FVector TargetLocation);
	void Shoot(TSubclassOf<class AProjectile> Projectile);
	void GetMouseLocationAndDirection(FVector& WorldLocation, FVector& WorldDirection);
	void FreeAimGamepad();
	void FreeAimMouse();
	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GamepadFreeAimSpeed = 10.f;
	
	virtual void BeginPlay() override;

private:
	const float MIN_AIM_DISTANCE = 200.f;
	
	AActor* Owner;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	FVector AimDirection;
	FVector TargetAimDirection;
	float TargetAimDistance;
	USkeletalMeshSocket const* BowSocket;
	TArray<AEnemy*> AutoAimTargets;
	AArcherPlayerController* PlayerController;
	FVector2D FreeAimGamepadCursor;
	
	FHitResult LineTraceFromStartToEnd(FVector start, FVector end) const;
	void InitializeCollisionTypes();

	FVector2D GetPlayerScreenPosition() const;
	void GetPlayerStickPositionAndDirection(float& PlayerScreenLocation, FVector2D& PlayerDirection);
	TArray<AActor*> GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection);
	void FreeAim(const FHitResult& Hit);
};
