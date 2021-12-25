#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "Camera/PlayerCameraManager.h"
#include "ArcherPlayerCameraManager.generated.h"

UCLASS()
class ARCHER_API AArcherPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	AArcherPlayerCameraManager();

	virtual void BeginPlay() override;

	AArcherCameraActorBase* OrbitalCamera;
	AArcherCameraActorBase* PrecisionCamera;
	FViewTargetTransitionParams TransitionParams;
	
public:
	FORCEINLINE void AddOrbitalCameraReference(AArcherCameraActorBase* Camera){OrbitalCamera = Camera;}
	FORCEINLINE void AddPrecisionCameraReference(AArcherCameraActorBase* Camera){PrecisionCamera = Camera;}
	
	void SetPrecisionCamera();
	void SetOrbitalCamera();
};
