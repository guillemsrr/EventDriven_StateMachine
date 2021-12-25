// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherPlayerCameraManager.h"

AArcherPlayerCameraManager::AArcherPlayerCameraManager()
{
	TransitionParams.BlendTime = 1.f;
	TransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_EaseOut;
	TransitionParams.BlendExp = 1.f;
	TransitionParams.bLockOutgoing = false;
}

void AArcherPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	StartCameraFade(0.f, 1.f, 1.f, FLinearColor::Black);
}

void AArcherPlayerCameraManager::SetPrecisionCamera()
{
	SetViewTarget(PrecisionCamera, TransitionParams);
}

void AArcherPlayerCameraManager::SetOrbitalCamera()
{
	SetViewTarget(OrbitalCamera, TransitionParams);
}
