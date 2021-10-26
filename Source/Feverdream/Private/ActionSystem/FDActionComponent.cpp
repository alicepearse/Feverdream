// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDActionComponent.h"
#include "ActionSystem/FDAction.h"

// Sets default values for this component's properties
UFDActionComponent::UFDActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UFDActionComponent::AddAction(TSubclassOf<UFDAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UFDAction* NewAction = NewObject<UFDAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UFDActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UFDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
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
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}

void UFDActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UFDAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
	
}

void UFDActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

