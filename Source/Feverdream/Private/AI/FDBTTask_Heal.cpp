// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FDBTTask_Heal.h"
#include "AIController.h"
#include "Components/FDAttributeComponent.h"

EBTNodeResult::Type UFDBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UFDAttributeComponent* AttributeComp = UFDAttributeComponent::GetAttributes(AIPawn);
	if (ensure(AttributeComp))
	{
		// Restore AI Health to MaxHealth
		float MaxHealth = AttributeComp->GetMaxHealth();
		AttributeComp->ApplyHealthChange(AIPawn, MaxHealth);
	}

	return EBTNodeResult::Succeeded;

}
