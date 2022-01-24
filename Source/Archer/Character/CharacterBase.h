// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract) //HideCategories = (Actor, Replication, Mobile, Input, LOD, Cooking, Rendering, Character, Camera)
class ARCHER_API ACharacterBase : public ACharacter //APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	int Health;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	virtual void Hit();

private:
	const int MAX_HEALTH = 1;
};
