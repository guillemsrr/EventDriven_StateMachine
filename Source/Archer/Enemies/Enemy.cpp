// Copyright (c) Guillem Serra. All Rights Reserved.

#include "Enemy.h"

#include "Components/CapsuleComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::Hit()
{
	Super::Hit();

	if(!IsAlive())
	{
		Die();
	}
}

void AEnemy::Die()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Controller->UnPossess();
}

