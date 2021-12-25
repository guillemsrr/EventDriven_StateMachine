// Fill out your copyright notice in the Description page of Project Settings.


#include "PrecisionCameraActor.h"

#include "ArcherPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

void APrecisionCameraActor::BeginPlay()
{
	Super::BeginPlay();

	AArcherPlayerCameraManager* CameraManager = static_cast<AArcherPlayerCameraManager*>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->AddOrbitalCameraReference(this);
}
