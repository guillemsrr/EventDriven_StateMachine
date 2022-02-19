// Copyright (c) Guillem Serra. All Rights Reserved.

#include "PrecisionCameraActor.h"
#include "ArcherPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"


void APrecisionCameraActor::BeginPlay()
{
	Super::BeginPlay();

	AArcherPlayerCameraManager* CameraManager = Cast<AArcherPlayerCameraManager>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->AddPrecisionCameraReference(this);
}

void APrecisionCameraActor::RotateCameraLeftRight(float Value)
{
}

void APrecisionCameraActor::RotateCameraUpDown(float Value)
{
}
