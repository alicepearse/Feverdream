// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FDBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UFDBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AI Pawn and Target Actor
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				APawn* AIPawn = AIController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceApart = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bInRange = DistanceApart < 1000.0f;

					bool bHasLineOfSight = false;
					if (bInRange)
					{
						bHasLineOfSight = AIController->LineOfSightTo(TargetActor);
					}
					
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bInRange && bHasLineOfSight));
				}
			}
		}
	}


}
