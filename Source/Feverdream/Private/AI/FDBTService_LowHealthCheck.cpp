// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FDBTService_LowHealthCheck.h"
#include "AIController.h"
#include "Components/FDAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFDBTService_LowHealthCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		if (ensure(AIController))
		{
			APawn* AIPawn = AIController->GetPawn();
			if (ensure(AIPawn))
			{
				UFDAttributeComponent* AttributeComp = UFDAttributeComponent::GetAttributes(AIPawn);
				if (ensure(AttributeComp))
				{
					float AIHealth = AttributeComp->GetHealth();
					float AIMaxHealth = AttributeComp->GetMaxHealth();

					if (!ensure(AIHealth && AIMaxHealth))
					{
						return;
					}

					bool bHasLowHealth = false;

					if (AIHealth < AIMaxHealth)
					{
						bHasLowHealth = true;
					}

					BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bHasLowHealth);
				}
			}
		}
	}
}
