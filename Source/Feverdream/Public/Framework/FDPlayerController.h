// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FDPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);


/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

	virtual void SetPawn(APawn* InPawn) override;

	/**
	 * Menu 
	 */

	 UPROPERTY(EditDefaultsOnly, Category = "UI")
	 TSubclassOf<UUserWidget> PauseMenuClass;

	 UPROPERTY()
	 UUserWidget* PauseMenuInstance;
	
	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu();

	virtual void SetupInputComponent() override;
};
