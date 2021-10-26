// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FDBTService_LowHealthCheck.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDBTService_LowHealthCheck : public UBTService
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector LowHealthKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
