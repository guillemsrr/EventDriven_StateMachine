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
	// Sets default values for this actor's properties
	AWaveSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnLocations;
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyClass;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartNextWave();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
