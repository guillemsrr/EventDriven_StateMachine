#include "ArchTrace.h"

#include "DrawDebugHelpers.h"
#include "Archer/Enemies/Enemy.h" 
#include "Archer/TimeManagement/SlowTimeManager.h"
#include "Archer/Utilities/Debug.h"
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

	PlayerController = static_cast<AArcherPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));

	//SetBowSocket();
}

void UArchTrace::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(this);
}

void UArchTrace::SetInterpolatedAimDirection(float DeltaTime)
{
	AimDirection = UKismetMathLibrary::VInterpTo(AimDirection, TargetAimDirection, DeltaTime, AimInterpolationSpeed);

	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	DrawDebugLine(GetWorld(), StartPosition, StartPosition + AimDirection * 1000.0f, FColor::Green, false, 0.01f, 0.f,
	              10.f);
}

void UArchTrace::InitializeCollisionTypes()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionTypes;
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
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
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
	DrawDebugLine(GetWorld(), hitResultLocation, hitResultLocation + FVector(0, 0, -10000.f), FColor::Red, false, 0.01f,
	              0.f, 10.f);
}

void UArchTrace::SetAimDirectionToTargetPosition(const FVector TargetLocation)
{
	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	TargetAimDirection = TargetLocation - StartPosition;
	TargetAimDirection.Normalize();
	DrawDebugLine(GetWorld(), StartPosition, TargetLocation, FColor::Red, false, 0.01f, 0.f,
	              10.f);
}

void UArchTrace::SetAimDirection(const AActor* ClosestTarget)
{
	SetAimDirectionToTargetPosition(ClosestTarget->GetActorLocation());
}

FVector2D UArchTrace::GetPlayerScreenPosition() const
{
	FVector2D PlayerScreenLocation;
	FVector StartPosition = BowSocket->GetSocketLocation(SkeletalMeshComponent);
	PlayerController->ProjectWorldLocationToScreen(
		StartPosition, PlayerScreenLocation, true);

	return PlayerScreenLocation;
}

AActor* UArchTrace::GetMouseClosestTarget()
{
	float MouseX;
	float MouseY;
	PlayerController->GetMousePosition(MouseX, MouseY);
	FVector2D MousePosition = FVector2D(MouseX, MouseY);

	FVector2D PlayerScreenLocation = GetPlayerScreenPosition();
	FVector2D PlayerDirection = MousePosition - PlayerScreenLocation;
	PlayerDirection.Normalize();

	TArray<AActor*> ClosestTargets = GetClosestTargetInPlayerDirection(PlayerScreenLocation, PlayerDirection);

	float ShortestDistance = TNumericLimits<float>::Max();
	AActor* ClosestTarget = nullptr;
	for (AActor* Target : ClosestTargets)
	{
		FVector2D TargetScreenLocation = GetActorScreenLocation(Target);

		float Distance = (MousePosition - TargetScreenLocation).Size();
		if (Distance < ShortestDistance)
		{
			ShortestDistance = Distance;
			ClosestTarget = Target;
		}
	}

	return ClosestTarget;
}

AActor* UArchTrace::GetGamepadClosestTarget()
{
	FVector2D PlayerScreenLocation = GetPlayerScreenPosition();

	float StickX;
	float StickY;
	PlayerController->GetInputAnalogStickState(EControllerAnalogStick::CAS_RightStick, StickX, StickY);
	FVector2D StickPosition = FVector2D(StickX, StickY);

	AActor* ClosestTarget = nullptr;
	float ShortestDistance = TNumericLimits<float>::Max();
	if (bAimOneMinimum && StickPosition == FVector2D(0))
	{
		for (AEnemy* AutoAimTarget : AutoAimTargets)
		{
			if(!AutoAimTarget->IsAlive()) continue;

			FVector2D TargetScreenLocation = GetActorScreenLocation(AutoAimTarget);
			float Distance = (PlayerScreenLocation - TargetScreenLocation).Size();

			if (Distance < ShortestDistance)
			{
				ShortestDistance = Distance;
				ClosestTarget = AutoAimTarget;
			}
		}

		return ClosestTarget;
	}

	FVector2D PlayerDirection = StickPosition;

	TArray<AActor*> ClosestTargets = GetClosestTargetInPlayerDirection(PlayerScreenLocation, PlayerDirection);
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Yellow, TEXT("Number targets: " + FString::FromInt(ClosestTargets.Num())));

	TArray<float> TargetDistances;
	float MaxDistance = 0;

	for (AActor* Target : ClosestTargets)
	{
		FVector2D TargetScreenLocation = GetActorScreenLocation(Target);
		float Distance = (PlayerScreenLocation - TargetScreenLocation).Size();
		TargetDistances.Add(Distance);
		if (Distance > MaxDistance)
		{
			MaxDistance = Distance;
		}
	}

	float ShortestRelativeDistance = TNumericLimits<float>::Max();
	float StickWeight = StickPosition.Size();
	
	for (int i = 0; i < ClosestTargets.Num(); i++)
	{
		float RelativeDistance = UKismetMathLibrary::Abs(StickWeight - (TargetDistances[i] / MaxDistance));
		if (RelativeDistance < ShortestRelativeDistance)
		{
			ShortestRelativeDistance = RelativeDistance;
			ClosestTarget = ClosestTargets[i];
		}
	}

	return ClosestTarget;
}

FVector2D UArchTrace::GetActorScreenLocation(AActor* Target)
{
	FVector2D TargetScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(
		Target->GetActorLocation(), TargetScreenLocation, true);

	return TargetScreenLocation;
}

TArray<AActor*> UArchTrace::GetClosestTargetInPlayerDirection(FVector2D PlayerScreenLocation, FVector2D PlayerDirection)
{
	PlayerDirection.Normalize();

	TArray<AActor*> ClosestTargets;
	AActor* ClosestTarget = nullptr;
	float SmallestAngle = TNumericLimits<float>::Max();
	for (AEnemy* Target : AutoAimTargets)
	{
		if(!Target->IsAlive()) continue;
		
		FVector2D TargetScreenLocation = GetActorScreenLocation(Target);
		FVector2D Direction = TargetScreenLocation - PlayerScreenLocation;
		Direction.Normalize();
		
		float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector2D::DotProduct(PlayerDirection, Direction)));

		if (AimAtAngle < MaxAimAngle)
		{
			ClosestTargets.Add(Target);
		}

		if (AimAtAngle < SmallestAngle)
		{
			SmallestAngle = AimAtAngle;
			ClosestTarget = Target;
		}
	}

	if (bAimOneMinimum && ClosestTargets.Num() == 0 && ClosestTarget)
	{
		ClosestTargets.Add(ClosestTarget);
	}
	return ClosestTargets;
}

void UArchTrace::Shoot(TSubclassOf<AProjectile> ProjectileTemplate)
{
	FRotator ProjectileRotation = TargetAimDirection.Rotation();
	FVector ProjectileLocation = BowSocket->GetSocketLocation(SkeletalMeshComponent) + TargetAimDirection * 10.f;

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
