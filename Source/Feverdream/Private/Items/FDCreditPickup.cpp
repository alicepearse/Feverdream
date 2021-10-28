// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDCreditPickup.h"
#include "Framework/FDPlayerState.h"

AFDCreditPickup::AFDCreditPickup()
{
	CreditIncreaseAmount = 1;
}

void AFDCreditPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	AFDPlayerState* PS = Cast<AFDPlayerState>(InstigatorPawn->GetPlayerState());
	if (PS)
	{
		PS->AddCredits(CreditIncreaseAmount);

		PickUp();
	}


}
