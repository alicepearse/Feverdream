// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FDGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/FDAICharacter.h"
#include "Components/FDAttributeComponent.h"
#include "EngineUtils.h"
#include "Characters/FDMainCharacter.h"
#include "Framework/FDPlayerState.h"

static TAutoConsoleVariable<bool>CVarSpawnBots(TEXT("fd.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);


AFDGameModeBase::AFDGameModeBase()
{
	SpawnTimeInterval = 2.0f;
	MaxBotCount = 10.0f;

	PlayerRespawnDelay = 2.0f;
	KillCredits = 10;
}


void AFDGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Respawn
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AFDGameModeBase::SpawnBotTimerElapsed, SpawnTimeInterval, true);

	// Spawn world items
	// ensure an item class is assigned
	if (ensure(ItemsToSpawnClasses.Num() > 0))
	{
		// Run EQS to find spawnable locations
		UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, ItemSpawnLocationQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
		if (ensure(QueryInstance))
		{
			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AFDGameModeBase::OnItemSpawnQueryCompleted);
		}
	}

}

void AFDGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot Spawning disabled via cvar 'CVarSpawnBots'."));
		return;
	}

	int32 NumAliveBots = 0;
	for (TActorIterator<AFDAICharacter> It(GetWorld()); It; ++It)
	{
		AFDAICharacter* Bot = *It;

		UFDAttributeComponent* AttributeComp = UFDAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NumAliveBots++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Found %i Bots"), NumAliveBots);

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	}

	if (NumAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("At max bot count. Skipping spawn"));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AFDGameModeBase::OnQueryCompleted);
	}
	
}

void AFDGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bot EQS Query Failed"));
		return;
	}


	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(AIEnemyClass, Locations[0], FRotator::ZeroRotator);
	}
}

void AFDGameModeBase::RespawnTimerElapsed(AController* PlayerController)
{
	if (ensure(PlayerController))
	{
		PlayerController->UnPossess();

		RestartPlayer(PlayerController);
	}
}


void AFDGameModeBase::OnItemSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn items EQS query failed"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	TArray<FVector> UsedLocations;

	int32 SpawnCounter = 0;

	// Stop attempting to spawn items if MaxSpawnedItems count has been reached or there are no more potential locations remaining
	while (SpawnCounter < MaxSpawnedItems && Locations.Num() > 0)
	{
		// Select random location from remaining Locations
		int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);

		FVector SelectedLocation = Locations[RandomLocationIndex];
		// Remove selected location to avoid spawning more than once in the same location
		Locations.RemoveAt(RandomLocationIndex);

		// Check minimum distance requirement and find location that meets it
		bool bValidLocation= true;
		for (FVector OtherLocation : UsedLocations)
		{
			float DistanceBetween = (SelectedLocation - OtherLocation).Size();

			if (DistanceBetween < MinItemDistanceApart)
			{
				bValidLocation = false;
				break;
			}
		}

		// If all locations failed the distance test
		if (!bValidLocation)
		{
			continue;
		}

		// Pick a random ItemToSpawnClass
		int32 RandomClassIndex = FMath::RandRange(0, ItemsToSpawnClasses.Num() - 1);
		TSubclassOf<AActor> RandomItemToSpawnClass = ItemsToSpawnClasses[RandomClassIndex];

		GetWorld()->SpawnActor<AActor>(RandomItemToSpawnClass, SelectedLocation, FRotator::ZeroRotator);

		// Save location for distance checks
		UsedLocations.Add(SelectedLocation);
		SpawnCounter++;
	}
}

void AFDGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	// Respawn player
	AFDMainCharacter* Player = Cast<AFDMainCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnTimerElapsed", Player->GetController());

		GetWorldTimerManager().SetTimer(TimerHandle, Delegate, PlayerRespawnDelay, false);
	}

	UE_LOG(LogTemp, Log, TEXT("On Actor Killed called: Victim %s, Killer %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));

	// Give credits for a kill
	AFDMainCharacter* KillerPlayer = Cast<AFDMainCharacter>(KillerActor);
	if (KillerPlayer)
	{
		AFDPlayerState* PS = Cast<AFDPlayerState>(KillerPlayer->GetPlayerState());
		if (PS)
		{
			PS->AddCredits(KillCredits);
		}
	}

}

void AFDGameModeBase::KillAll()
{
	for (TActorIterator<AFDAICharacter> It(GetWorld()); It; ++It)
	{
		AFDAICharacter* Bot = *It;

		UFDAttributeComponent* AttributeComp = UFDAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this); // TODO: Pass in player for kill credit?
		}
	}
}
