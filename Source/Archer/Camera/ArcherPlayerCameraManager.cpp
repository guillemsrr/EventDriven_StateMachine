// Copyright (c) Guillem Serra. All Rights Reserved.


#include "ArcherPlayerCameraManager.h"

#include "ArcherCameraActorBase.h"
#include "Archer/General/ArcherGameMode.h"
#include "Archer/TimeManagement/SlowTimeManager.h"

AArcherPlayerCameraManager::AArcherPlayerCameraManager()
{
	TransitionParams.BlendTime = 1.f;
	TransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_EaseInOut;
	TransitionParams.BlendExp = 1.f;
	TransitionParams.bLockOutgoing = false;
}

void AArcherPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black);
}

void AArcherPlayerCameraManager::SetCurrentCamera(AArcherCameraActorBase* Camera)
{
	CurrentCamera = Camera;
	SetViewTarget(Camera, TransitionParams);
}

void AArcherPlayerCameraManager::SetPrecisionCameraView()
{
	DisableCurrentCameraInput();
	SetCurrentCamera(PrecisionCamera);
	EnableCurrentCameraInput();
}

void AArcherPlayerCameraManager::SetOrbitalCameraView()
{
	DisableCurrentCameraInput();
	SetCurrentCamera(OrbitalCamera);
	EnableCurrentCameraInput();
}

void AArcherPlayerCameraManager::SetNormalCameraView()
{
	DisableCurrentCameraInput();
	SetCurrentCamera(OrbitalCamera);
}

void AArcherPlayerCameraManager::RotateLeft()
{
	OrbitalCamera->RotateCameraLeftRight(-90.f);
}

void AArcherPlayerCameraManager::RotateRight()
{
	OrbitalCamera->RotateCameraLeftRight(90.f);
}

void AArcherPlayerCameraManager::EnableCurrentCameraInput()
{
	CurrentCamera->EnableInput(GetOwningPlayerController());
}

void AArcherPlayerCameraManager::DisableCurrentCameraInput()
{
	CurrentCamera->DisableInput(GetOwningPlayerController());
}

void AArcherPlayerCameraManager::Initialize(USlowTimeManager* TimeManager)
{
	TimeManager->AddFreeTicker(OrbitalCamera);
	TimeManager->AddFreeTicker(PrecisionCamera);
}
