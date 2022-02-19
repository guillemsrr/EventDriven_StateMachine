// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OrbitalCameraActor.h"
#include "ArcherPlayerCameraManager.generated.h"

class USlowTimeManager;
class AArcherGameMode;
class AArcherCameraActorBase;

UCLASS()
class ARCHER_API AArcherPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	AArcherPlayerCameraManager();

public:
	virtual void BeginPlay() override;

	FORCEINLINE void AddOrbitalCameraReference(AOrbitalCameraActor* Camera) { OrbitalCamera = Camera; }
	FORCEINLINE void AddPrecisionCameraReference(AArcherCameraActorBase* Camera) { PrecisionCamera = Camera; }

	void Initialize(USlowTimeManager* TimeManager);
	void SetCurrentCamera(AArcherCameraActorBase* Camera);
	void SetPrecisionCameraView();
	void SetOrbitalCameraView();
	void SetNormalCameraView();

	UFUNCTION(BlueprintCallable)
	void SetOrbitalCameraPivotPoint(USceneComponent* PivotPoint){OrbitalCamera->SetPivotPoint(PivotPoint);}

private:
	UPROPERTY()
	AOrbitalCameraActor* OrbitalCamera;
	UPROPERTY()
	AArcherCameraActorBase* PrecisionCamera;
	UPROPERTY()
	AArcherCameraActorBase* CurrentCamera;
	UPROPERTY()
	FViewTargetTransitionParams TransitionParams;
	
	void EnableCurrentCameraInput();
	void DisableCurrentCameraInput();
};
