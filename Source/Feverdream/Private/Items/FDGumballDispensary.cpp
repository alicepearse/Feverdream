// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDGumballDispensary.h"

AFDGumballDispensary::AFDGumballDispensary()
{
	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassMeshFixed"));
	GlassMesh->SetupAttachment(DispensaryMeshBase);
	GlassMesh->SetStaticMesh(GlassMeshUnbroken);
}

void AFDGumballDispensary::DeactivateDispensary()
{
	Super::DeactivateDispensary();

	GlassMesh->SetStaticMesh(GlassMeshBroken);
}

void AFDGumballDispensary::ReactivateDispensary()
{
	Super::ReactivateDispensary();

	GlassMesh->SetStaticMesh(GlassMeshUnbroken);
}


void AFDGumballDispensary::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

}

