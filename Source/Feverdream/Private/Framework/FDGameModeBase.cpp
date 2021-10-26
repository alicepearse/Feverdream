// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FDGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/FDAICharacter.h"
#include "Components/FDAttributeComponent.h"
#include "EngineUtils.h"
#include "Characters/FDMainCharacter.h"

static TAutoConsoleVariable<bool>CVarSpawnBots(TEXT("fd.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);


AFDGameModeBase::AFDGameModeBase()
{
	SpawnTimeInterval = 2.0f;
	MaxBotCount = 10.0f;

	PlayerRespawnDelay = 2.0f;
}


void AFDGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AFDGameModeBase::SpawnBotTimerElapsed, SpawnTimeInterval, true);
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

void AFDGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	AFDMainCharacter* Player = Cast<AFDMainCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnTimerElapsed", Player->GetController());

		GetWorldTimerManager().SetTimer(TimerHandle, Delegate, PlayerRespawnDelay, false);
	}

	UE_LOG(LogTemp, Log, TEXT("On Actor Killed called: Victim %s, Killer %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
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
