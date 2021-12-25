
#include "OrbitalCameraActor.h"

#include "ArcherPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

AOrbitalCameraActor::AOrbitalCameraActor()
{
	
}

void AOrbitalCameraActor::BeginPlay()
{
	Super::BeginPlay();

	AArcherPlayerCameraManager* CameraManager = static_cast<AArcherPlayerCameraManager*>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->AddOrbitalCameraReference(this);
	CameraManager->SetViewTarget(this);
}
