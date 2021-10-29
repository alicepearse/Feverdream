// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FDPlayerState.generated.h"

class AFDSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, AFDPlayerState*, PlayerState, int32, PlayerCredits, int32, Delta);
/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	AFDPlayerState();
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Credits")
	int32 PlayerCredits;

public:

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetPlayerCredits() const;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void AddCredits(int32 DeltaCredits);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	bool RemoveCredits(int32 DeltaCredits);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChanged OnCreditsChanged;

	/**
	 * Save/Load 
	 */

	 UFUNCTION(BlueprintNativeEvent)
	 void SavePlayerState(UFDSaveGame* SaveObject);

	 UFUNCTION(BlueprintNativeEvent)
	 void LoadPlayerState(UFDSaveGame* SaveObject);

};
