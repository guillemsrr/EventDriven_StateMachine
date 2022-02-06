#include "ArchTrace.h"

#include "DrawDebugHelpers.h"
#include "Archer/Enemies/Enemy.h"
#include "Archer/TimeManagement/SlowTimeManager.h"
#include "Archer/Weapons/Projectile.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UArchTrace::UArchTrace()
{
	PrimaryComponentTick.TickInterval = 0.01;
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	SetComponentTickEnabled(true);
}

void UArchTrace::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	InitializeCollisionTypes();
	//SetBowSocket();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("BeginPlay ARCHTRACE"));
}

void UArchTrace::InitializeComponent()
{
	Super::InitializeComponent();
	Owner = GetOwner();
	InitializeCollisionTypes();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("InitializeComponent ARCHTRACE"));
}

void UArchTrace::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(this);
}

void UArchTrace::SetInterpolatedAimDirection(float DeltaTime)
{
	AimDirection = UKismetMathLibrary::VInterpTo(AimDirection, TargetAimDirection, DeltaTime, AimInterpolationSpeed);

	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	DrawDebugLine(GetWorld(), StartPosition, StartPosition+AimDirection*1000.0f, FColor::Green, false, 0.01f, 0.f, 10.f);
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

void UArchTrace::SetBowSocket(USkeletalMeshComponent* skeletalMeshComponent)
{
	this->SkeletalMeshComponent = skeletalMeshComponent;
	BowSocket = SkeletalMeshComponent->GetSocketByName(BowSocketName);
}

void UArchTrace::GetMouseLocationAndDirection(FVector& WorldLocation, FVector& WorldDirection)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		WorldLocation, WorldDirection);
}

//TODO -> use PlayerController's GetHitUnderCursor ?¿
void UArchTrace::FreeAim()
{
	FVector WorldLocation;
	FVector WorldDirection;
	GetMouseLocationAndDirection(WorldLocation, WorldDirection);

	FHitResult mouseHitResult = LineTraceFromStartToEnd(WorldLocation, WorldLocation + WorldDirection * 10000);
	if (!mouseHitResult.IsValidBlockingHit())
	{
		return;
	}

	DrawDebugPoint(GetWorld(), mouseHitResult.Location, 10.f, FColor::Blue);

	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	float Distance = UKismetMathLibrary::Vector_Distance(mouseHitResult.Location, StartPosition);
	//GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Yellow, TEXT("Distance: " + FString::SanitizeFloat(Distance)));

	if (Distance < 200.f)
	{
		return;
	}
	TargetAimDirection = mouseHitResult.Location - StartPosition;
	TargetAimDirection.Normalize();
	FVector end = mouseHitResult.Location + TargetAimDirection * 100;
	FHitResult hitResult = LineTraceFromStartToEnd(StartPosition, end);
	if (!hitResult.IsValidBlockingHit())
	{
		return;
	}

	FVector hitResultLocation = hitResult.Location;
	TargetAimDirection = hitResultLocation - StartPosition;
	TargetAimDirection.Normalize();
	
	DrawDebugPoint(GetWorld(), hitResult.Location, 10.f, FColor::Green);
	DrawDebugLine(GetWorld(), StartPosition, hitResultLocation, FColor::Red, false, 0.01f, 0.f, 10.f);
	DrawDebugLine(GetWorld(), hitResultLocation, hitResultLocation + FVector(0, 0, -10000.f), FColor::Red, false, 0.01f, 0.f, 10.f);
}

void UArchTrace::SetAimDirection(const FVector TargetLocation)
{
	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	TargetAimDirection = TargetLocation - StartPosition;
	TargetAimDirection.Normalize();
	DrawDebugLine(GetWorld(), StartPosition, TargetLocation, FColor::Red, false, 0.01f, 0.f,
	              10.f);
}

void UArchTrace::SetAimDirection(const AActor* ClosestTarget)
{
	SetAimDirection(ClosestTarget->GetActorLocation());
}

void UArchTrace::GetPlayerMousePositionAndDirection(FVector2D& PlayerScreenLocation, FVector2D& PlayerDirection)
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MouseX, MouseY);
	FVector2D MousePosition = FVector2D(MouseX, MouseY);

	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(
		StartPosition, PlayerScreenLocation, true);

	PlayerDirection = MousePosition - PlayerScreenLocation;
	PlayerDirection.Normalize();
}

AActor* UArchTrace::GetClosestTarget()
{
	FVector2D PlayerScreenLocation;
	FVector2D PlayerDirection;
	GetPlayerMousePositionAndDirection(PlayerScreenLocation, PlayerDirection);

	return GetClosestTargetInPlayerDirection(PlayerScreenLocation, PlayerDirection);
}

AActor* UArchTrace::GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection)
{
	float SmallestAngle = TNumericLimits<float>::Max();
	AActor* ClosestTarget = nullptr;
	for (AActor* Target : AutoAimTargets)
	{
		FVector2D TargetScreenLocation;
		UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(
			Target->GetActorLocation(), TargetScreenLocation, true);

		FVector2D Direction = TargetScreenLocation - PlayerScreenLocation;
		Direction.Normalize();
		float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector2D::DotProduct(PlayerDirection, Direction)));
		if (AimAtAngle < SmallestAngle)
		{
			SmallestAngle = AimAtAngle;
			ClosestTarget = Target;
		}
	}

	return ClosestTarget;
}

void UArchTrace::Shoot(TSubclassOf<AProjectile> ProjectileTemplate)
{
	FRotator ProjectileRotation = TargetAimDirection.Rotation();
	FVector ProjectileLocation = BowSocket->GetSocketLocation(SkeletalMeshComponent) + TargetAimDirection*10.f;

	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();

	AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileTemplate, ProjectileLocation, ProjectileRotation,
	                                                         SpawnParams);
	if (Projectile)
	{
		Projectile->FireInDirection(TargetAimDirection);
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
