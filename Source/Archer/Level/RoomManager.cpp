// Copyright (c) Guillem Serra. All Rights Reserved.

#include "RoomManager.h"

#include "Components/BoxComponent.h"

ARoomManager::ARoomManager()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	CameraPivot = CreateDefaultSubobject<USceneComponent>("Camera pivot");
	PlayerCollision = CreateDefaultSubobject<UBoxComponent>("Player Collision");
}

void ARoomManager::BeginPlay()
{
	Super::BeginPlay();
	
}