// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class ARCHER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	class UBlackboardComponent* BlackboardComponent;
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, Category= AI)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	FName PlayerKey;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	class UBehaviorTree* BehaviorTree;
public:

	FORCEINLINE FName GetPlayerKey() const { return PlayerKey; }
	
private:
	AEnemyAIController();
	
	virtual void BeginPlay() override;
};
