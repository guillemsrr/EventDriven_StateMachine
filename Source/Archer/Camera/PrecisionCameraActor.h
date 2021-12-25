// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "PrecisionCameraActor.generated.h"

UCLASS()
class ARCHER_API APrecisionCameraActor : public AArcherCameraActorBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
