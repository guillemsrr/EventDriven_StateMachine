// Copyright (c) Guillem Serra. All Rights Reserved.


#include "ArcherCameraActorBase.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


AArcherCameraActorBase::AArcherCameraActorBase()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bTickEvenWhenPaused = true;
	//UE_LOG(LogTemp, Warning, TEXT("float: %f"), t);
}

void AArcherCameraActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->bIsCameraMoveableWhenPaused = true;
	SetupPlayerInputComponent();
}

void AArcherCameraActorBase::SetupPlayerInputComponent()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
