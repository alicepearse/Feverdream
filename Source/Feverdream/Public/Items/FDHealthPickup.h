// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/FDPickupBase.h"
#include "FDHealthPickup.generated.h"

UCLASS()
class FEVERDREAM_API AFDHealthPickup : public AFDPickupBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDHealthPickup();

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;



};
