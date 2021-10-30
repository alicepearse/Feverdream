// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_STATS_GROUP(TEXT("FEVERDREAM_Game"), STATGROUP_FEVERDREAM, STATCAT_Advanced);

// Debug function for action system networking
static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* World = WorldContext->GetWorld();
	if (World)
	{
		FString NetPrefix = World->IsNetMode(NM_Client) ? "[CLIENT] " : "[SERVER] ";
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPrefix + Msg);
		}
	}
	
}