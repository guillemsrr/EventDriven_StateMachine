// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCameraActorBase.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AArcherCameraActorBase::AArcherCameraActorBase()
{
	Camera = CreateDefaultSubobject<ACameraActor>("Camera");
	Camera->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

