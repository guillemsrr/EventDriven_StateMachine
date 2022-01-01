#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "ArcherCharacter.generated.h"

class USlowTimeManager;
UCLASS(config=Game)
class AArcherCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AArcherCharacter();

	void Initialize(USlowTimeManager* TimeManager);
	void DisableMovement();
	void EnableMovement();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UArcherMovement* CharacterMovement;
	class UArchTrace* Arch;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Aim();
	void StopAim();
	void StartShoot();
	void ReleaseShoot();
};
