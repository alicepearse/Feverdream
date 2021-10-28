// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDItemChest.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFDItemChest::AFDItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBase"));
	RootComponent = ChestBase;

	ChestBaseInterior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBaseInterior"));
	ChestBaseInterior->SetupAttachment(ChestBase);

	ChestLid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestLid"));
	ChestLid->SetupAttachment(ChestBase);

	ChestLidInterior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestLidInterior"));
	ChestLidInterior->SetupAttachment(ChestLid);

	// Initialize default values
	TargetPitchOpenLid = 110.f;

	SetReplicates(true);

}

void AFDItemChest::OnRep_LidOpened()
{
	float CurrentPitch = bIsLidOpen ? TargetPitchOpenLid : 0.0f;
	ChestLid->SetRelativeRotation(FRotator(0.0f, 0.0f, CurrentPitch));
}

void AFDItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bIsLidOpen = !bIsLidOpen;
	OnRep_LidOpened();
}

void AFDItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFDItemChest, bIsLidOpen);
}
