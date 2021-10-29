// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDAction.h"
#include "ActionSystem/FDActionComponent.h"
#include "../Feverdream.h"
#include "Net/UnrealNetwork.h"


void UFDAction::Initialize(UFDActionComponent* NewActionComp)
{
	ActionComponent = NewActionComp;
}

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
	
// 	LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UFDActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
/*	ActionComp->ActiveGameplayTags.AppendTags(BlocksTags);*/

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;

	if (GetOwningComponent()->GetOwnerRole() == ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}
	
	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);
}

void UFDAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StopAction called"));

// 	LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);

// 	ensureAlways(bIsRunning);

	UFDActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
/*	ActionComp->ActiveGameplayTags.RemoveTags(BlocksTags);*/

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}

UWorld* UFDAction::GetWorld() const
{
	// Outer is set when creating new action object 
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}



bool UFDAction::IsRunning()
{
	return RepData.bIsRunning;
}


void UFDAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

UFDActionComponent* UFDAction::GetOwningComponent() const
{
	return ActionComponent;
}

void UFDAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UFDAction, RepData);
	DOREPLIFETIME(UFDAction, ActionComponent);
	DOREPLIFETIME(UFDAction, TimeStarted);
}