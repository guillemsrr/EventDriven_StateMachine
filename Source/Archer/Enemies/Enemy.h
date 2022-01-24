// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Archer/Character/CharacterBase.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class ARCHER_API AEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Hit() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Die();

};
