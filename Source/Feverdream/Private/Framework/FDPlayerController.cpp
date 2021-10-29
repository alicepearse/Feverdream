// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FDPlayerController.h"

void AFDPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}
