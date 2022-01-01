// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCameraActorBase.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


AArcherCameraActorBase::AArcherCameraActorBase()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	float t = GetActorTickInterval();
	SetActorTickInterval(t);
	
	//UE_LOG(LogTemp, Warning, TEXT("float: %f"), t);
	
}

void AArcherCameraActorBase::BeginPlay()
{
	Super::BeginPlay();
	//no funciona
	//Camera->CustomTimeDilation = GetWorld()->GetDeltaSeconds();

	SetupPlayerInputComponent();
}

void AArcherCameraActorBase::SetupPlayerInputComponent()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
