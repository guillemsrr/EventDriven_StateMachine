// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"

#include "Animation/CharacterAnimations.h"

#include "Archer/Player/ArcherPlayerController.h"

#include "GameFramework/Character.h"
#include "Mechanics/CharacterMechanics.h"
#include "Movement/CharacterMovement.h"
#include "StateMachines/Locomotion/LocomotionStateMachine.h"
#include "StateMachines/Mechanics/MechanicsStateMachine.h"

#include "ArcherCharacter.generated.h"

class USlowTimeManager;

UCLASS(config=Game)
class AArcherCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AArcherCharacter();
	virtual ~AArcherCharacter() override;

	void Initialize(USlowTimeManager* TimeManager);
	void DisableMovement() const;
	void EnableMovement() const;

	///TODO-> I can't override this Pawn virtual method?
	//UFUNCTION(BlueprintCallable, Category=Pawn)
	//virtual FRotator APawn::GetBaseAimRotation() const override;

	FRotator GetAimRotator() const;
	FRotator GetAimRotationRelativeToMovement() const;

	FORCEINLINE FCharacterMechanics* GetCharacterMechanics() const { return CharacterMechanics; }
	FORCEINLINE FCharacterMovement* GetArcherMovement() const { return ArcherMovement; }
	FORCEINLINE UCharacterAnimations* GetArcherAnimations() const { return CharacterAnimations; }
	FORCEINLINE FMechanicsStateMachine* GetMechanicsStateMachine() const { return MechanicsStateMachine; }
	FORCEINLINE AArcherPlayerController* GetPlayerController() const { return PlayerController; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Archer")
	UArchTrace* Arch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Archer")
	UCharacterAnimations* CharacterAnimations;

	UPROPERTY(EditDefaultsOnly, Category= "Archer")
	TSubclassOf<AProjectile> ProjectileClass;

	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	FLocomotionStateMachine* LocomotionStateMachine;
	FMechanicsStateMachine* MechanicsStateMachine;
	FCharacterMovement* ArcherMovement;
	FCharacterMechanics* CharacterMechanics;
	AArcherPlayerController* PlayerController;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartRunning();
	void StopRunning();
	void Aim();
	void StopAim();
	void StartShoot();
	void ReleaseShoot();
	void StartFreeAim();
	void StopFreeAim();
	void PrecisionAimX(float Value);
	void PrecisionAimY(float Value);
};
