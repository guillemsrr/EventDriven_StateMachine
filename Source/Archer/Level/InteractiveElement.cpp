// Copyright (c) Guillem Serra. All Rights Reserved.

#include "InteractiveElement.h"
#include "Components/BoxComponent.h"


AInteractiveElement::AInteractiveElement()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComponent->InitBoxExtent(FVector(30.f, 30.f, 30.f));
	RootComponent = BoxComponent;
	//BoxComponent->SetCollisionProfileName(UCollisionProfile::);

	BoxComponent->CanCharacterStepUpOn = ECB_No;
	BoxComponent->SetShouldUpdatePhysicsVolume(false);
	BoxComponent->SetCanEverAffectNavigation(false);
	BoxComponent->bDynamicObstacle = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);
}

void AInteractiveElement::BeginPlay()
{
	Super::BeginPlay();

	//BoxComponent->OnComponentBeginOverlap.Add()
}

void AInteractiveElement::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void AInteractiveElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

