// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDHealthPickup.h"
#include "Components/FDAttributeComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFDHealthPickup::AFDHealthPickup()
{

}

void AFDHealthPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UFDAttributeComponent* AttributeComp = Cast<UFDAttributeComponent>(InstigatorPawn->GetComponentByClass(UFDAttributeComponent::StaticClass()));
	if (ensure(AttributeComp))
	{
		// Prevent pickup if instigator is at max health
		if (AttributeComp->GetHealth() < AttributeComp->GetMaxHealth())
		{
			AttributeComp->ApplyHealthChange(this, 20.0f);

			if (ensure(PickupEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupEffect, GetActorLocation(), GetActorRotation());
			}

			Destroy();
		}
	}
}


