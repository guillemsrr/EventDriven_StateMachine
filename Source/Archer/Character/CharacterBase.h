// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract) //HideCategories = (Actor, Replication, Mobile, Input, LOD, Cooking, Rendering, Character, Camera)
class ARCHER_API ACharacterBase : public ACharacter //APawn
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	virtual void Hit();
	
protected:
	int Health;
	
	virtual void BeginPlay() override;

private:
	const int MAX_HEALTH = 1;
};
