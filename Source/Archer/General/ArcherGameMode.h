// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcherGameMode.generated.h"

UCLASS(minimalapi)
class AArcherGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AArcherGameMode();

public:
	enum GameplayMode
	{
		Normal,
		Orbital,
		Precision,
		Menu
	};

	FORCEINLINE GameplayMode GetCurrentGameplayMode() const {return CurrentGameplayMode;}
	FORCEINLINE void SetCurrentGameplayMode(GameplayMode GameplayMode) {CurrentGameplayMode = GameplayMode;}
	
private:
	GameplayMode CurrentGameplayMode;
};



