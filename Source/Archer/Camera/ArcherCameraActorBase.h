#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.generated.h"

UCLASS()
class ARCHER_API AArcherCameraActorBase : public AActor
{
protected:
	GENERATED_BODY()
	AArcherCameraActorBase();
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent();
	virtual void RotateCameraUpDown(float Value) PURE_VIRTUAL(AArcherCameraActorBase::RotateCameraUpDown);
	virtual void RotateCameraLeftRight(float Value) PURE_VIRTUAL(AArcherCameraActorBase::RotateCameraLeftRight);
};
