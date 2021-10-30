// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "FDGameModeBase.generated.h"


class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class UFDSaveGame;
class UDataTable;
class UFDAIEnemyData;

/** DataTable Row for spawning AIEnemy in game mode */
USTRUCT(BlueprintType)
struct FAIEnemyInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	FAIEnemyInfoRow()
	{
		Weight = 1.0f;
		SpawnCost = 5.0f;
		KillReward = 20.0f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId AIEnemyID;

// 	UFDAIEnemyData* AIEnemyData;
// 	TSubclassOf<AActor>AIEnemyClass;

	/** Relative chance to pick this AIEnemy */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	/** Points required by game mode to spawn this unit */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	/** Amount of credits awarded to killer of this unit */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward;
};

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

	/** All available AIEnemy */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* AIEnemyTable;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimeInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float MaxBotCount;

// 	UPROPERTY(EditDefaultsOnly, Category = "AI")
// 	TSubclassOf<AActor> AIEnemyClass;

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

	/** Function called when AIEnemy data is loaded */
	void OnAIEnemyLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation);

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


	/**
	 * Save/Load Game
	 */

protected:
	
	FString SlotName;

	UPROPERTY()
	UFDSaveGame* CurrentSavedGame;

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	void WriteSaveGame();

	void LoadSaveGame();
	
};
