// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDAction.h"

void UFDAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StartAction called"));
}

void UFDAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StopAction called"));
}

UWorld* UFDAction::GetWorld() const
{
	// Outer is set when creating new action object 
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}
