// Copyright (c) Guillem Serra. All Rights Reserved.

#include "CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Health = MAX_HEALTH;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACharacterBase::IsAlive() const
{
	return Health > 0;
}

void ACharacterBase::Hit()
{
	Health--;
}

