// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDPickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AFDPickupBase::AFDPickupBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MeshEffect"));
	MeshEffect->SetupAttachment(MeshComp);

/*	InteractionComponent = CreateDefaultSubobject<UFDInteractionComponent>(TEXT("InteractionComponent"));*/
}

void AFDPickupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Logic in derived class
}

