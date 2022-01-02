#pragma once

#include "CoreMinimal.h"
#include "ArcherPlayerController.generated.h"

class AArcherPlayerCameraManager;
class AArcherCharacter;
class AArcherGameMode;
class USlowTimeManager;

UCLASS()
class ARCHER_API AArcherPlayerController : public APlayerController
{
	GENERATED_BODY()
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
	
public:
	void Initialize();
};
