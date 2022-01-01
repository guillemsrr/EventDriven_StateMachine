﻿// Fill out your copyright notice in the Description page of Project Settings.


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
	if(!TimeFreeActors.IsValidIndex(0))
	{
		return;
	}
	UGameplayStatics::SetGlobalTimeDilation(TimeFreeActors[0], 1.f);

	for (AActor* Actor : TimeFreeActors)
	{
		Actor->CustomTimeDilation = 1.f;
	}

	for (UActorComponent* ActorComponent : TimeFreeActorComponents)
	{
		//ActorComponent->Timedil(Delta);
	}
}

void USlowTimeManager::SetSlowModeTimeDilation()
{
	float Delta = TimeFreeActors[0]->GetWorld()->GetDeltaSeconds();
	
	UGameplayStatics::SetGlobalTimeDilation(TimeFreeActors[0], 0.2f);

	for (AActor* Actor : TimeFreeActors)
	{
		//Actor->CustomTimeDilation = 5.f;
	}

	for (UActorComponent* ActorComponent : TimeFreeActorComponents)
	{
		//ActorComponent->Timedil(Delta);
	}
}