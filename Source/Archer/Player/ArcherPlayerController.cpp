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
}

void AArcherPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentGameMode = Cast<AArcherGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ArcherCharacter = Cast<AArcherCharacter>(GetCharacter());
	CameraManager = Cast<AArcherPlayerCameraManager>(PlayerCameraManager);

	SlowTimeManager->SetWorldContext(this);
	SetNormalMode();
}

void AArcherPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//TODO -> transfer into Blueprints for the automatic name changing
	InputComponent->BindAction("Pause", IE_Pressed, this, &AArcherPlayerController::OnPausePressed);
	InputComponent->BindAction("OrbitMode", IE_Pressed, this, &AArcherPlayerController::OnSlowModePressed);
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
	if(IsPaused)
	{
		UGameplayStatics::SetGlobalTimeDilation(ArcherCharacter, 1.f);
		CameraManager->SetOrbitalCameraView();
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(ArcherCharacter, 0.0f);
		CameraManager->SetNormalCameraView();
	}

	IsPaused = !IsPaused;
}

void AArcherPlayerController::SetPrecisionMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Precision);
	//ArcherCharacter->EnableInput(this);
	ArcherCharacter->DisableMovement();
	SlowTimeManager->SetSlowModeTimeDilation();
	CameraManager->SetPrecisionCameraView();
}

void AArcherPlayerController::SetNormalMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Normal);
	ArcherCharacter->EnableInput(this);
	ArcherCharacter->EnableMovement();
	//ArcherCharacter->EnableInput(this);

	SlowTimeManager->SetGlobalTimeDilation();
	CameraManager->SetNormalCameraView();
}

void AArcherPlayerController::SetOrbitalMode()	
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Orbital);
	ArcherCharacter->DisableMovement();
	//ArcherCharacter->DisableInput(this);
	
	SlowTimeManager->SetSlowModeTimeDilation();
	CameraManager->SetOrbitalCameraView();
}

void AArcherPlayerController::Initialize()
{
	CameraManager->Initialize(SlowTimeManager);
	ArcherCharacter->Initialize(SlowTimeManager);
}
