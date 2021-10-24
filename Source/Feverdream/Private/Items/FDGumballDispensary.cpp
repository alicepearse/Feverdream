// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDGumballDispensary.h"

AFDGumballDispensary::AFDGumballDispensary()
{
	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassMeshFixed"));
	GlassMesh->SetupAttachment(DispensaryMeshBase);
	GlassMesh->SetStaticMesh(GlassMeshUnbroken);

	// Set default values
	bIsDispensaryActivated = true;
	DeactivationTime = 10.0f;
}

void AFDGumballDispensary::DeactivateDispensary()
{
	GlassMesh->SetStaticMesh(GlassMeshBroken);

	bIsDispensaryActivated = false;

	// Reactive the dispensary after elapsed time(seconds)
	GetWorldTimerManager().SetTimer(TimerHandle_ReactivateDispensary, this, &AFDGumballDispensary::ReactivateDispensary, DeactivationTime);
}

void AFDGumballDispensary::ReactivateDispensary()
{
	GlassMesh->SetStaticMesh(GlassMeshUnbroken);

	bIsDispensaryActivated = true;
}

void AFDGumballDispensary::Interact_Implementation(APawn* InstigatorPawn)
{
	// Check that the dispensary is activated
	if (bIsDispensaryActivated)
	{
		Super::Interact_Implementation(InstigatorPawn);

		// Deactivate the dispensary for amount time(seconds)
		DeactivateDispensary();
	}

}

