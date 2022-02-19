// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcherPlayerController.generated.h"

class AArcherPlayerCameraManager;
class AArcherCharacter;
class AArcherGameMode;
class USlowTimeManager;

UCLASS(Blueprintable)
class ARCHER_API AArcherPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool IsPlayerUsingGamepad;
	
	void Initialize();

private:
	AArcherPlayerController();

	AArcherGameMode* CurrentGameMode;
	AArcherCharacter* ArcherCharacter;
	AArcherPlayerCameraManager* CameraManager;
	USlowTimeManager* SlowTimeManager;

	bool IsPaused;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void InitInputSystem() override;
	
	void OnSlowModePressed();
	void OnPausePressed();
	void SetPrecisionMode();
	void SetNormalMode();
	void SetOrbitalMode();
};
