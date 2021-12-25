#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "OrbitalCameraActor.generated.h"

UCLASS()
class ARCHER_API AOrbitalCameraActor : public AArcherCameraActorBase
{
	GENERATED_BODY()

	AOrbitalCameraActor();

	virtual void BeginPlay() override;
};
