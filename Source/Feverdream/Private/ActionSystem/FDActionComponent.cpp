// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDActionComponent.h"
#include "ActionSystem/FDAction.h"

// Sets default values for this component's properties
UFDActionComponent::UFDActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UFDActionComponent::AddAction(AActor* Instigator, TSubclassOf<UFDAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UFDAction* NewAction = NewObject<UFDAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}

void UFDActionComponent::RemoveAction(UFDAction* ActionToRemove)
{
	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

bool UFDActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UFDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run : %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FailedMsg);

				continue;
			}
			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UFDActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UFDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

void UFDActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UFDAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
	
}

void UFDActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, DebugMsg);

}

