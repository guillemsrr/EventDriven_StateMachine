
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

	SetNormalMode();
}

void AArcherPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//TODO -> transfere into Blueprints for the automatic name changing
	InputComponent->BindAction("Pause", IE_Pressed, this, &AArcherPlayerController::OnSlowModePressed);
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

void AArcherPlayerController::SetPrecisionMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Precision);
	ArcherCharacter->EnableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
	CameraManager->SetPrecisionCameraView();
}

void AArcherPlayerController::SetNormalMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Normal);
	ArcherCharacter->EnableInput(this);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	CameraManager->SetNormalCameraView();
}

void AArcherPlayerController::SetOrbitalMode()
{
	CurrentGameMode->SetCurrentGameplayMode(AArcherGameMode::Orbital);
	
	ArcherCharacter->DisableInput(this);
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);
	CameraManager->SetOrbitalCameraView();
}