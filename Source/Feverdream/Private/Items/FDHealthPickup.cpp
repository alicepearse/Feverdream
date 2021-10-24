// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDHealthPickup.h"

// Sets default values
AFDHealthPickup::AFDHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFDHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFDHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

