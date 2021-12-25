#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "Mechanics/ArchTrace.h"
#include "Movement/ArcherMovement.h"
#include "ArcherCharacter.generated.h"

UCLASS(config=Game)
class AArcherCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AArcherCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

private:
	class UArcherMovement* CharacterMovement;
	class UArchTrace* Arch;
	class APrecisionCameraActor* CameraActor;

protected:
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Aim();
	void StopAim();
	void StartShoot();
	void ReleaseShoot();
};

