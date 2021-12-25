// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherPlayerController.h"
#include "Archer/Camera/ArcherPlayerCameraManager.h"
#include "Archer/Character/ArcherCharacter.h"
#include "Archer/General/ArcherGameMode.h"
#include "Kismet/GameplayStatics.h"

AArcherPlayerController::AArcherPlayerController()
{
	PlayerCameraManagerClass = AArcherPlayerCameraManager::StaticClass();
	bShowMouseCursor = true;
}

void AArcherPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameMode = static_cast<AArcherGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
	ArcherCharacter = static_cast<AArcherCharacter*>(GetCharacter());
	CameraManager = static_cast<AArcherPlayerCameraManager*>(PlayerCameraManager);
}

void AArcherPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AArcherPlayerController::OnPausePressed);
	InputComponent->BindAxis("MoveForward", this, &AArcherPlayerController::RotateCameraUpDown).bConsumeInput = false;
	InputComponent->BindAxis("MoveRight", this, &AArcherPlayerController::RotateCameraLeftRight).bConsumeInput = false;
}

void AArcherPlayerController::OnPausePressed()
{
	if(CurrentGameMode->GetCurrentGameplayMode() == AArcherGameMode::Character)
	{
		SetPrecisionMode();
	}
	else if(CurrentGameMode->GetCurrentGameplayMode() == AArcherGameMode::World)
	{
		SetCharacterMode();
	}
}

void AArcherPlayerController::SetPrecisionMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::World);
	ArcherCharacter->DisableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
	CameraManager->SetPrecisionCamera();
}

void AArcherPlayerController::SetCharacterMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Character);
	ArcherCharacter->EnableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	CameraManager->SetOrbitalCamera();
}

void AArcherPlayerController::RotateCameraUpDown(float Value)
{
	if(CurrentGameMode->GetCurrentGameplayMode() != AArcherGameMode::World)
	{
		return;
	}

}

void AArcherPlayerController::RotateCameraLeftRight(float Value)
{
	if(CurrentGameMode->GetCurrentGameplayMode() != AArcherGameMode::World)
	{
		return;
	}

	
}
