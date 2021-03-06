// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDeadSignature);

UCLASS(Abstract)
class ARCHER_API ACharacterBase : public ACharacter //APawn
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	virtual void Hit();
	
	UPROPERTY(BlueprintAssignable)
	FCharacterDeadSignature OnCharacterDead;
	
protected:

	int Health;
	
	virtual void BeginPlay() override;
	virtual void Die();

private:
	const int MAX_HEALTH = 1;
};
