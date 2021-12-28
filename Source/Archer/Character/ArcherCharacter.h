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

private:
	class UArcherMovement* CharacterMovement;
	class UArchTrace* Arch;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Aim();
	void StopAim();
	void StartShoot();
	void ReleaseShoot();
};

