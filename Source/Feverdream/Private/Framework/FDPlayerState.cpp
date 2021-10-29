// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FDPlayerState.h"
#include "Framework/FDSaveGame.h"

AFDPlayerState::AFDPlayerState()
{
	PlayerCredits = 0;
}

int32 AFDPlayerState::GetPlayerCredits() const
{
	return PlayerCredits;
}

void AFDPlayerState::AddCredits(int32 DeltaCredits)
{
	if (!ensure(DeltaCredits > 0.0f))
	{
		return;
	}

	PlayerCredits += DeltaCredits;
	
	OnCreditsChanged.Broadcast(this, PlayerCredits, DeltaCredits);
}

bool AFDPlayerState::RemoveCredits(int32 DeltaCredits)
{
	if (!ensure(DeltaCredits > 0.0f))
	{
		return false;
	}

	if (PlayerCredits < DeltaCredits)
	{
		// insufficient amount of credits available
		return false;
	}

	PlayerCredits -= DeltaCredits;

	OnCreditsChanged.Broadcast(this, PlayerCredits, -DeltaCredits);

	return true;
}

void AFDPlayerState::SavePlayerState_Implementation(UFDSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = PlayerCredits;
	}
}

void AFDPlayerState::LoadPlayerState_Implementation(UFDSaveGame* SaveObject)
{
	if (SaveObject)
	{
		PlayerCredits = SaveObject->Credits;
	}
}

