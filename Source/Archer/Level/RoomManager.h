// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.generated.h"

UCLASS()
class ARCHER_API ARoomManager : public AActor
{
	GENERATED_BODY()

public:
	ARoomManager();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* CameraPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* PlayerCollision;
	
	virtual void BeginPlay() override;
};
