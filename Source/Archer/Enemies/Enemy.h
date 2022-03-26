// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Archer/Character/CharacterBase.h"
#include "Enemy.generated.h"

UCLASS()
class ARCHER_API AEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	virtual void Die() override;
};
