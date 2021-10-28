// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDAction.h"
#include "ActionSystem/FDActionComponent.h"


bool UFDAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	UFDActionComponent* ActionComp = GetOwningComponent();

	if (ActionComp->ActiveGameplayTags.HasAny(BlocksTags))
	{
		return false;
	}
	return true;
}

void UFDAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StartAction called"));

	UFDActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
/*	ActionComp->ActiveGameplayTags.AppendTags(BlocksTags);*/

	bIsRunning = true;
}

void UFDAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StopAction called"));

	ensureAlways(bIsRunning);

	UFDActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
/*	ActionComp->ActiveGameplayTags.RemoveTags(BlocksTags);*/

	bIsRunning = false;
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

bool UFDAction::IsRunning()
{
	return bIsRunning;
}

UFDActionComponent* UFDAction::GetOwningComponent() const
{
	return Cast<UFDActionComponent>(GetOuter());
}