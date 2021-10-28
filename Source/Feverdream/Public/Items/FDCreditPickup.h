// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/FDPickupBase.h"
#include "FDCreditPickup.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDCreditPickup : public AFDPickupBase
{
	GENERATED_BODY()

public:

	AFDCreditPickup();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 CreditIncreaseAmount;

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
