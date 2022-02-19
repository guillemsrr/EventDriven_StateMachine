// Copyright (c) Guillem Serra. All Rights Reserved.


#include "BTS_FindPlayer.h"

#include "EnemyAIController.h"
#include "Archer/Character/ArcherCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_FindPlayer::UBTS_FindPlayer()
{
}

void UBTS_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* ArcherCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AEnemyAIController* AIController = static_cast<AEnemyAIController*>(OwnerComp.GetAIOwner());
	if(AIController)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetPlayerKey(), ArcherCharacter);
	}
}
