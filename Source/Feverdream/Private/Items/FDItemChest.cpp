// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDItemChest.h"

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

}

// Called when the game starts or when spawned
void AFDItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFDItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFDItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ChestLid->SetRelativeRotation(FRotator(0.0f, 0.0f, TargetPitchOpenLid));
}

