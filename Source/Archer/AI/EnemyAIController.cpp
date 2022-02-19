// Copyright (c) Guillem Serra. All Rights Reserved.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController()
{
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	//BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));

	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UseBlackboard(BlackboardData, BlackboardComponent);
	RunBehaviorTree(BehaviorTree);
}
