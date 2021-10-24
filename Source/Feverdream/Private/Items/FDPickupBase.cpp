// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDPickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/FDAttributeComponent.h"

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


	UFDAttributeComponent* AttributeComp = Cast<UFDAttributeComponent>(InstigatorPawn->GetComponentByClass(UFDAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		if (AttributeComp->GetHealth() < AttributeComp->GetMaxHealth())
		{
			AttributeComp->ApplyHealthChange(20.0f);

			if (ensure(PickupEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupEffect, GetActorLocation(), GetActorRotation());
			}

			Destroy();
		}
	}

}

