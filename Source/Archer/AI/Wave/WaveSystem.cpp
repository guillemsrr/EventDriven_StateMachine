// Copyright (c) Guillem Serra. All Rights Reserved.


#include "WaveSystem.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


AWaveSystem::AWaveSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWaveSystem::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InputComponent->BindAction("NextWave", IE_Pressed, this, &AWaveSystem::StartNextWave);
}

void AWaveSystem::StartNextWave()
{
	UWorld* World = GetWorld();
	const FActorSpawnParameters SpawnParams;

	for (AActor* SpawnLocation : SpawnLocations)
	{
		World->SpawnActor<AEnemy>(EnemyClass, SpawnLocation->GetActorLocation(), SpawnLocation->GetActorRotation(), SpawnParams);
		//UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), EnemyClass, nullptr, SpawnLocation->GetActorLocation(), SpawnLocation->GetActorRotation());
	}
}

void AWaveSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
