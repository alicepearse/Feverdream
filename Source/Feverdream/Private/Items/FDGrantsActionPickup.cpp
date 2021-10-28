// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDGrantsActionPickup.h"
#include "ActionSystem/FDActionComponent.h"
#include "Characters/FDMainCharacter.h"
#include "ActionSystem/FDAction.h"

void AFDGrantsActionPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	// Check if player already has action class active, if so don't grant action


	AFDMainCharacter* Player = Cast<AFDMainCharacter>(InstigatorPawn);
	if (Player)
	{
		UFDActionComponent* ActionComp = Cast<UFDActionComponent>(Player->GetComponentByClass(UFDActionComponent::StaticClass()));
		if (ActionComp && ensure(ActionToGrant)/* TODO: && check for class*/)
		{
			if (!ActionComp->ActiveGameplayTags.HasTag(GrantingActionTag))
			{
				// Grant action
				ActionComp->AddAction(Player, ActionToGrant);

				PickUp();
			}
		}
	}


}
