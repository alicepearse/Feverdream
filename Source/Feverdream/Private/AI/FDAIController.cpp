// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FDAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AFDAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("BehaviorTree is nullptr. Please assign BehaviorTree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

// 	// Temporary location the AI can use to move to - hacky do not leave in here
// 	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
// 	if (PlayerPawn)
// 	{
// 		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", PlayerPawn->GetActorLocation());
// 
// 		GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
// 	}
}
