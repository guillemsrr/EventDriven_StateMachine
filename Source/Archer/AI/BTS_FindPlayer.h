// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_FindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARCHER_API UBTS_FindPlayer : public UBTService
{
	GENERATED_BODY()

	UBTS_FindPlayer();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
