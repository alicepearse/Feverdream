// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDVendingDispensary.h"
#include "Characters/FDMainCharacter.h"
#include "Framework/FDPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

AFDVendingDispensary::AFDVendingDispensary()
{
	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassMeshFixed"));
	GlassMesh->SetupAttachment(DispensaryMeshBase);
	GlassMesh->SetStaticMesh(GlassMeshUnbroken);

	CreditCost = 10;
}

void AFDVendingDispensary::DeactivateDispensary()
{
	Super::DeactivateDispensary();

	GlassMesh->SetStaticMesh(GlassMeshBroken);
}

void AFDVendingDispensary::ReactivateDispensary()
{
	Super::ReactivateDispensary();

	GlassMesh->SetStaticMesh(GlassMeshUnbroken);
}

FText AFDVendingDispensary::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	return FText::Format(LOCTEXT("VendingDispensary_InteractMessage", "Cost {0} Credits"), CreditCost);
}

void AFDVendingDispensary::Interact_Implementation(APawn* InstigatorPawn)
{
	// Check if instigator has enough credits to use dispensary
	AFDMainCharacter* PlayerCharacter = Cast<AFDMainCharacter>(InstigatorPawn);
	if (PlayerCharacter)
	{
		AFDPlayerState* PS = Cast<AFDPlayerState>(PlayerCharacter->GetPlayerState());
		if (PS)
		{
			if (PS->GetPlayerCredits() < CreditCost)
			{
				UE_LOG(LogTemp, Warning, TEXT("You do not have enough credits"));
				return;
			}

			// Remove the credit cost from the player credits
			PS->RemoveCredits(CreditCost);

			// Spawn items and deactivate dispensary
			Super::Interact_Implementation(InstigatorPawn);
		}
	}
}

#undef LOCTEXT_NAMESPACE