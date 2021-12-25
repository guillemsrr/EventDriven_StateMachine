#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcherCameraActorBase.generated.h"

UCLASS()
class ARCHER_API AArcherCameraActorBase : public AActor
{
	GENERATED_BODY()

public:
	AArcherCameraActorBase();

protected:
	class ACameraActor* Camera;
};
