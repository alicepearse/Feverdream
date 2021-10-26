// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDItemDispensaryBase.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFDItemDispensaryBase::AFDItemDispensaryBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DispensaryMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = DispensaryMeshBase;

	DispenseEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MeshEffect"));
	DispenseEffect->SetupAttachment(DispensaryMeshBase);

	// Set default values
	bIsDispensaryActivated = true;
	DeactivationTime = 10.0f;
}

void AFDItemDispensaryBase::DeactivateDispensary()
{
	SetDispensaryState(false);

	// Reactive the dispensary after elapsed time(seconds)
	GetWorldTimerManager().SetTimer(TimerHandle_ReactivateDispensary, this, &AFDItemDispensaryBase::ReactivateDispensary, DeactivationTime);
}

void AFDItemDispensaryBase::ReactivateDispensary()
{
	SetDispensaryState(true);
}

void AFDItemDispensaryBase::SetDispensaryState(bool bNewIsActivated)
{
	SetActorEnableCollision(bNewIsActivated);
}


void AFDItemDispensaryBase::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(DispensedItemsClass))
	{
		// Spawn dispensed items
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, GetActorRotation().Roll);
		// Spawn the item 100cm in front of the dispensary and 100cm above the ground
		FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y + 100.0f,GetActorLocation().Z + 100.0f);

		DispensedItems = GetWorld()->SpawnActor<AActor>(DispensedItemsClass, SpawnLocation, SpawnRotation, SpawnParams);

		DeactivateDispensary();
	}
}

