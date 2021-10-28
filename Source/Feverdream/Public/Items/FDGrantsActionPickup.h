// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/FDPickupBase.h"
#include "GameplayTagContainer.h"
#include "FDGrantsActionPickup.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDGrantsActionPickup : public AFDPickupBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTag GrantingActionTag;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TSubclassOf<UFDAction> ActionToGrant;


public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
