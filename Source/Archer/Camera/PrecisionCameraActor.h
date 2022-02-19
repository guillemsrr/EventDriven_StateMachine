// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "PrecisionCameraActor.generated.h"

UCLASS()
class ARCHER_API APrecisionCameraActor : public AArcherCameraActorBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void RotateCameraLeftRight(float Value) override;
	virtual void RotateCameraUpDown(float Value) override;
	
};
