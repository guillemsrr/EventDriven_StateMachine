// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Archer/Enemies/Enemy.h"

#include "GameFramework/Actor.h"
#include "WaveSystem.generated.h"

UCLASS(Blueprintable)
class ARCHER_API AWaveSystem : public AActor
{
	GENERATED_BODY()

public:
	AWaveSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnLocations;
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyClass;
	
	virtual void BeginPlay() override;

	void StartNextWave();

public:
	virtual void Tick(float DeltaTime) override;
};
