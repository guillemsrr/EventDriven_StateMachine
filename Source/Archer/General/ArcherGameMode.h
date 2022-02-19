// Copyright (c) Guillem Serra. All Rights Reserved.

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
	
	GameplayMode CurrentGameplayMode;

	FORCEINLINE GameplayMode GetCurrentGameplayMode() const {return CurrentGameplayMode;}
	FORCEINLINE void SetCurrentGameplayMode(GameplayMode GameplayMode) {CurrentGameplayMode = GameplayMode;}

protected:
	void BeforeStartPlay();
	virtual void StartPlay() override;
	void AfterStartPlay();
};



