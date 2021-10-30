// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FDAIEnemyData.generated.h"

class UFDAction;

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDAIEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,  BlueprintReadOnly, Category = "SpawnInfo")
	TSubclassOf<AActor> AIEnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnInfo")
	TArray<TSubclassOf<UFDAction>> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UTexture2D* Icon;

	FPrimaryAssetId GetPrimaryAssetId() const override 
	{
		return FPrimaryAssetId("AIEnemy", GetFName());
	}
	
};
