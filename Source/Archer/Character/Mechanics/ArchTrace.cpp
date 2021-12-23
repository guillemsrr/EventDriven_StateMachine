﻿#include "ArchTrace.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

UArchTrace::UArchTrace()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	SetComponentTickEnabled(true);
}

void UArchTrace::BeginPlay()
{
	Super::BeginPlay();
	InitializeCollisionTypes();
	Owner = GetOwner();
}

void UArchTrace::InitializeCollisionTypes()
{
	TArray<TEnumAsByte<enum EObjectTypeQuery>> CollisionTypes;
	CollisionTypes.Emplace(ECollisionChannel::ECC_PhysicsBody);
	CollisionTypes.Emplace(ECollisionChannel::ECC_WorldStatic);
	CollisionTypes.Emplace(ECollisionChannel::ECC_WorldDynamic);
	CollisionTypes.Emplace(ECollisionChannel::ECC_Pawn);
	
	CollisionObjectQueryParams = FCollisionObjectQueryParams(CollisionTypes);
	CollisionQueryParams = FCollisionQueryParams();
	CollisionQueryParams.AddIgnoredActor(GetOwner());
}

void UArchTrace::Aim()
{
	IsAiming = true;

	//LineTraceObjects();
	//StartLineTraceTimer();
}

void UArchTrace::Shoot(TSubclassOf<class AProjectile> ProjectileTemplate)
{
	if(!IsAiming)
	{
		return;
	}
	
	// Get the camera transform.
	FVector CharacterLocation = Owner->GetActorLocation();
	// Skew the aim to be slightly upwards.
	FRotator MuzzleRotation = Owner->GetActorRotation();
	//MuzzleRotation.Pitch += 10.0f;

	// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
	MuzzleOffset = AimDirection*100.f;

	// Transform MuzzleOffset from camera space to world space.
	FVector MuzzleLocation = CharacterLocation + FTransform(AimDirection).TransformVector(MuzzleOffset);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Owner;
		SpawnParams.Instigator =  Owner->GetInstigator();

		// Spawn the projectile at the muzzle.
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileTemplate, MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			Projectile->FireInDirection(AimDirection);
		}
	}
}

void UArchTrace::StartLineTraceTimer()
{
	GetOwner()->GetWorldTimerManager().SetTimer(
		AimTimerHandle,
		this,
		&UArchTrace::LineTraceCoroutine,
		0.1f);
}

void UArchTrace::StopAiming()
{
	IsAiming = false;
}

void UArchTrace::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	if(IsAiming)
	{
		LineTraceCoroutine();
	}
}

void UArchTrace::LineTraceObjects()
{
	FVector worldLocation;
	FVector worldDirection;
	bool achieved = UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		worldLocation, worldDirection);

	if (!achieved)
	{
		return;
	}

	FHitResult mouseHitResult = LineTraceFromStartToEnd(worldLocation, worldLocation + worldDirection * 10000);
	if(!mouseHitResult.IsValidBlockingHit())
	{
		return;
	}

	DrawDebugPoint(GetWorld(), mouseHitResult.Location, 10.f, FColor::Blue);
	
	FVector start = GetOwner()->GetTransform().GetLocation();
	AimDirection = mouseHitResult.Location - start;
	AimDirection.Normalize();
	FVector end = mouseHitResult.Location + AimDirection*100;
	FHitResult hitResult = LineTraceFromStartToEnd(start, end);
	if (!hitResult.IsValidBlockingHit())
	{
		return;
	}

	DrawDebugPoint(GetWorld(), hitResult.Location, 10.f, FColor::Green);
	DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.01f, 0.f, 5.f);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("hit"));
}

FHitResult UArchTrace::LineTraceFromStartToEnd(FVector start, FVector end) const
{
	FHitResult hitResult;
	
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		start,
		end,
		CollisionObjectQueryParams,
		CollisionQueryParams
		);

	if(!hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("nope"));
	}

	return hitResult;
}

void UArchTrace::LineTraceCoroutine()
{
	if(!IsAiming) return;

	LineTraceObjects();
	StartLineTraceTimer();
}
