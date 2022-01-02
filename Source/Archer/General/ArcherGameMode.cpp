// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcherGameMode.h"

#include "ArcherGameState.h"
#include "Archer/Player/ArcherPlayerController.h"
#include "Kismet/GameplayStatics.h"

AArcherGameMode::AArcherGameMode()
{
	PlayerControllerClass = AArcherPlayerController::StaticClass();
	GameStateClass = AArcherGameState::StaticClass();
}

void AArcherGameMode::StartPlay()
{
	BeforeStartPlay();
	Super::StartPlay();
	AfterStartPlay();
}

void AArcherGameMode::BeforeStartPlay()
{
	GetWorld()->bIsCameraMoveableWhenPaused = true; // Fixes TXAA/MotionBlur glitches.
}

void AArcherGameMode::AfterStartPlay()
{
	AArcherPlayerController* PlayerController = Cast<AArcherPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->Initialize();
}