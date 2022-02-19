// Copyright (c) Guillem Serra. All Rights Reserved.


#include "SlowTimeManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

void USlowTimeManager::AddFreeTicker(AActor* Ticker)
{
	TimeFreeActors.Add(Ticker);
}

void USlowTimeManager::AddFreeTicker(UActorComponent* Ticker)
{
	TimeFreeActorComponents.Add(Ticker);
}

void USlowTimeManager::SetGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(WorldContext->GetWorld(), NORMAL_TIME_DILATION);

	for (AActor* Actor : TimeFreeActors)
	{
		Actor->CustomTimeDilation = NORMAL_TIME_DILATION;
	}

	for (UActorComponent* ActorComponent : TimeFreeActorComponents)
	{
		//ActorComponent->Time(Delta);
	}
}

void USlowTimeManager::SetSlowModeTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(WorldContext->GetWorld(), SLOW_TIME_DILATION);

	for (AActor* Actor : TimeFreeActors)
	{
		Actor->CustomTimeDilation = 1/SLOW_TIME_DILATION;
	}

	for (UActorComponent* ActorComponent : TimeFreeActorComponents)
	{
		//ActorComponent->Timedil(Delta);
	}
}
