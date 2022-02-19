// Copyright (c) Guillem Serra. All Rights Reserved.

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
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;

	virtual void Hit() override;
	
protected:
	virtual void BeginPlay() override;

private:
	void Die();

};
