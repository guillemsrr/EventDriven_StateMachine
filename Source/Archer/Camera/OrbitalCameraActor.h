#pragma once

#include "CoreMinimal.h"
#include "ArcherCameraActorBase.h"
#include "OrbitalCameraActor.generated.h"

UCLASS()
class ARCHER_API AOrbitalCameraActor : public AArcherCameraActorBase
{
	GENERATED_BODY()

	AOrbitalCameraActor();

protected:
	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Zoom = 100.f;
	
	virtual void BeginPlay() override;
	virtual void RotateCameraLeftRight(float Value) override;
	virtual void RotateCameraUpDown(float Value) override;
	virtual void SetupPlayerInputComponent() override;
	void CorrectRollRotation();

private:
	void LookAtRoot();
};
