// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FDGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFDGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FEVERDREAM_API IFDGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);

	/**
	 * UI
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	FText GetInteractText(APawn* InstigatorPawn);

	/**
	 * Save/Load 
	 */

	 // called after the actor state was restored from a save game file
	 UFUNCTION(BlueprintNativeEvent)
	 void OnActorLoaded();
};
