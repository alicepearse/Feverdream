// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "FDGameModeBase.generated.h"


class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AFDGameModeBase();

protected:

	/**
	 * AI Enemy
	 */

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimeInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float MaxBotCount;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> AIEnemyClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	/**
	 * Player
	 */

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float PlayerRespawnDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	int32 KillCredits;

	/**
	 * World
	 */

	UPROPERTY(EditDefaultsOnly, Category = "World")
	TArray<TSubclassOf<AActor>> ItemsToSpawnClasses;

	UPROPERTY(EditDefaultsOnly, Category = "World")
	UEnvQuery* ItemSpawnLocationQuery;

	UPROPERTY(EditDefaultsOnly, Category = "World")
	int32 MaxSpawnedItems;

	UPROPERTY(EditDefaultsOnly, Category = "World")
	float MinItemDistanceApart;

public:
	virtual void StartPlay() override;

protected:

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnTimerElapsed(AController* PlayerController);

	UFUNCTION()
	void OnItemSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:

	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);

	/**
	 * Debugging Console Commands
	 */

	UFUNCTION(Exec)
	void KillAll();
	
};
