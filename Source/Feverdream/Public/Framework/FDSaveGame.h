// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FDSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:

	/** Identifier for which actor this data belongs */
	UPROPERTY()
	FString ActorName;

	/** The transform data for moveable actors */
	UPROPERTY()
	FTransform Transform;

	// Auto Serialize
	UPROPERTY()
	TArray<uint8> ByteData;

};

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;

	UPROPERTY()
	int32 Credits;

	
};
