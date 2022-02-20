// Copyright (c) Guillem Serra. All Rights Reserved.

#include "ArcherPlayerController.h"

#include "Archer/Camera/ArcherPlayerCameraManager.h"
#include "Archer/Character/ArcherCharacter.h"
#include "Archer/General/ArcherGameMode.h"
#include "Archer/TimeManagement/SlowTimeManager.h"

#include "GameFramework/PlayerInput.h"

#include "Kismet/GameplayStatics.h"

AArcherPlayerController::AArcherPlayerController()
{
	PlayerCameraManagerClass = AArcherPlayerCameraManager::StaticClass();
	bShowMouseCursor = true;
	bShouldPerformFullTickWhenPaused = true;
	SlowTimeManager = CreateDefaultSubobject<USlowTimeManager>("Slow time manager");
	InputMode = FInputModeGameAndUI();
}

void AArcherPlayerController::Initialize()
{
	ArcherCharacter = Cast<AArcherCharacter>(GetCharacter());
	ArcherCharacter->Initialize(SlowTimeManager);
	CameraManager->Initialize(SlowTimeManager);

	//SetInputMode(InputMode);
	SlowTimeManager->SetWorldContext(this);
	SetNormalMode();
}

void AArcherPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AArcherPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CurrentGameMode = Cast<AArcherGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CameraManager = Cast<AArcherPlayerCameraManager>(PlayerCameraManager);
}

void AArcherPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//TODO -> transfer into Blueprints for the automatic name changing
	InputComponent->BindAction("Pause", IE_Pressed, this, &AArcherPlayerController::OnPausePressed);
	InputComponent->BindAction("OrbitMode", IE_Pressed, this, &AArcherPlayerController::OnSlowModePressed);

	InputComponent->BindAction("Rotate Left", IE_Pressed, CameraManager, &AArcherPlayerCameraManager::RotateLeft);
	InputComponent->BindAction("Rotate Right", IE_Pressed, CameraManager, &AArcherPlayerCameraManager::RotateRight);
}

void AArcherPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

/*#if ARCHER_WITH_EDITOR
	// We need to reset it back
	PlayerInput->SetBind(TEXT("F1"), TEXT("viewmode wireframe"));
	PlayerInput->SetBind(TEXT("F9"), TEXT("shot showui"));
	PlayerInput->SetBind(TEXT("F5"), TEXT("viewmode ShaderComplexity"));
#endif*/
}

void AArcherPlayerController::OnSlowModePressed()
{
	if(CurrentGameMode->GetCurrentGameplayMode() != AArcherGameMode::Orbital)
	{
		SetOrbitalMode();
	}
	else
	{
		SetNormalMode();
	}
}

void AArcherPlayerController::OnPausePressed()
{
	if(bIsPaused)
	{
		UGameplayStatics::SetGlobalTimeDilation(ArcherCharacter, 1.f);
		CameraManager->SetOrbitalCameraView();
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(ArcherCharacter, 0.0f);
		CameraManager->SetNormalCameraView();
	}

	bIsPaused = !bIsPaused;
}

void AArcherPlayerController::SetPrecisionMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Precision);
	ArcherCharacter->DisableMovement();
	SlowTimeManager->SetSlowModeTimeDilation();
	CameraManager->SetPrecisionCameraView();
}

void AArcherPlayerController::SetNormalMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Normal);
	ArcherCharacter->EnableInput(this);
	ArcherCharacter->EnableMovement();

	SlowTimeManager->SetGlobalTimeDilation();
	CameraManager->SetNormalCameraView();
}

void AArcherPlayerController::SetOrbitalMode()	
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Orbital);
	ArcherCharacter->DisableMovement();
	
	SlowTimeManager->SetSlowModeTimeDilation();
	CameraManager->SetOrbitalCameraView();
}
