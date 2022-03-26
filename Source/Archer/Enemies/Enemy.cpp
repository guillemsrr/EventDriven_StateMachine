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

void AEnemy::Die()
{
	Super::Die();
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	if(Controller)
	{
		Controller->UnPossess();
	}
}

