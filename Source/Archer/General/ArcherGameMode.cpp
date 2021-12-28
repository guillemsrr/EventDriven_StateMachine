// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcherGameMode.h"

#include "ArcherGameState.h"
#include "Archer/Player/ArcherPlayerController.h"

AArcherGameMode::AArcherGameMode()
{
	PlayerControllerClass = AArcherPlayerController::StaticClass();
	GameStateClass = AArcherGameState::StaticClass();
}
