#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "Camera/PlayerCameraManager.h"
#include "ArcherPlayerCameraManager.generated.h"

UCLASS()
class ARCHER_API AArcherPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	DECLARE_DELEGATE(CameraArrived)
	
	AArcherPlayerCameraManager();

	virtual void BeginPlay() override;

	AArcherCameraActorBase* OrbitalCamera;
	AArcherCameraActorBase* PrecisionCamera;
	AArcherCameraActorBase* CurrentCamera;
	FViewTargetTransitionParams TransitionParams;
	
public:
	FORCEINLINE void AddOrbitalCameraReference(AArcherCameraActorBase* Camera){OrbitalCamera = Camera;}
	FORCEINLINE void AddPrecisionCameraReference(AArcherCameraActorBase* Camera){PrecisionCamera = Camera;}

	void SetCurrentCamera(AArcherCameraActorBase* Camera);
	void SetPrecisionCameraView();
	void SetOrbitalCameraView();
	void SetNormalCameraView();

private:
	void EnableCurrentCameraInput();
	void DisableCurrentCameraInput();
};
