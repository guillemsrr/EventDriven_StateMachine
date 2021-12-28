#pragma once

#include "CoreMinimal.h"
#include "ArcherPlayerController.generated.h"

UCLASS()
class ARCHER_API AArcherPlayerController : public APlayerController
{
	GENERATED_BODY()
	AArcherPlayerController();

	class AArcherGameMode* CurrentGameMode;
	class AArcherCharacter* ArcherCharacter;
	class AArcherPlayerCameraManager* CameraManager;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void OnSlowModePressed();
	void SetPrecisionMode();
	void SetNormalMode();
	void SetOrbitalMode();
};
