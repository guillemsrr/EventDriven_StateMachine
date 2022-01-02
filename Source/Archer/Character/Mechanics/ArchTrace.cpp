#include "ArchTrace.h"

#include "DrawDebugHelpers.h"
#include "Archer/Enemies/Enemy.h"
#include "Archer/TimeManagement/SlowTimeManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UArchTrace::UArchTrace()
{
	PrimaryComponentTick.TickInterval = 0.01;
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	SetComponentTickEnabled(true);
}

void UArchTrace::InitializeComponent()
{
	Super::InitializeComponent();
	Owner = GetOwner();
	InitializeCollisionTypes();
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("InitializeComponent ARCHTRACE"));
}

void UArchTrace::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(this);
}

void UArchTrace::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	InitializeCollisionTypes();
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("BeginPlay ARCHTRACE"));
}

//TODO: Can I extract it to a "Coroutine" instead of checking every tick?¿ 
void UArchTrace::Tick()
{
	if(!IsAiming) return;

	if(!IsAutoAiming)
	{
		FreeAim();
	}
	else
	{
		AutoAim();
	}
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
	CollisionQueryParams.AddIgnoredActor(Owner);
}

void UArchTrace::Aim()
{
	IsAiming = true;
}

void UArchTrace::StopAiming()
{
	IsAiming = false;
}

void UArchTrace::StartAutoAim()
{
	//TODO-> Get enemies from a global controller
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);

	AutoAimTargets = Enemies;
	IsAutoAiming = true;
}

void UArchTrace::StopAutoAim()
{
	IsAutoAiming = false;
}

void UArchTrace::GetMouseLocationAndDirection(FVector& worldLocation, FVector& worldDirection)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		worldLocation, worldDirection);
}

//TODO -> use PlayerController's GetHitUnderCursor ?¿
void UArchTrace::FreeAim()
{
	FVector WorldLocation;
	FVector WorldDirection;
	GetMouseLocationAndDirection(WorldLocation, WorldDirection);

	FHitResult mouseHitResult = LineTraceFromStartToEnd(WorldLocation, WorldLocation + WorldDirection * 10000);
	if(!mouseHitResult.IsValidBlockingHit())
	{
		return;
	}

	DrawDebugPoint(GetWorld(), mouseHitResult.Location, 10.f, FColor::Blue);
	
	FVector Start = Owner->GetActorLocation();
	AimDirection = mouseHitResult.Location - Start;
	AimDirection.Normalize();
	FVector end = mouseHitResult.Location + AimDirection*100;
	FHitResult hitResult = LineTraceFromStartToEnd(Start, end);
	if (!hitResult.IsValidBlockingHit())
	{
		return;
	}

	DrawDebugPoint(GetWorld(), hitResult.Location, 10.f, FColor::Green);
	DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Red, false, 0.01f, 0.f, 5.f);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("hit"));
}

void UArchTrace::AutoAim()
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MouseX, MouseY);
	FVector2D MousePosition = FVector2D(MouseX, MouseY);

	FVector PlayerWorldPosition = Owner->GetActorLocation();
	FVector2D PlayerScreenLocation;
	UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(PlayerWorldPosition, PlayerScreenLocation, true);
	
	FVector2D PlayerDirection = MousePosition - PlayerScreenLocation;
	PlayerDirection.Normalize();
	
	float SmallestAngle = TNumericLimits<float>::Max();
	AActor* ClosestTarget = nullptr;
	for (AActor* Target : AutoAimTargets)
	{
		FVector2D TargetScreenLocation;
		UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(Target->GetActorLocation(), TargetScreenLocation, true);

		FVector2D Direction = TargetScreenLocation - PlayerScreenLocation;
		Direction.Normalize();
		float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector2D::DotProduct(PlayerDirection, Direction)));
		if(AimAtAngle < SmallestAngle)
		{
			SmallestAngle = AimAtAngle;
			ClosestTarget = Target;
		}
	}

	if(!ClosestTarget) return;
	
	AimDirection = ClosestTarget->GetActorLocation() - PlayerWorldPosition;
	AimDirection.Normalize();
	DrawDebugLine(GetWorld(), PlayerWorldPosition, ClosestTarget->GetActorLocation(), FColor::Red, false, 0.01f, 0.f, 5.f);
}

void UArchTrace::Shoot(TSubclassOf<class AProjectile> ProjectileTemplate)
{
	if(!IsAiming)
	{
		return;
	}
	
	// Get the camera transform.
	FVector CharacterLocation = Owner->GetTransform().GetLocation();
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

FHitResult UArchTrace::LineTraceFromStartToEnd(FVector start, FVector end) const
{
	FHitResult hitResult;
	
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		start,
		end,
		CollisionObjectQueryParams,
		CollisionQueryParams
		);

	return hitResult;
}
