// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FDBTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	
	UFDBTTask_RangedAttack();

protected:
	
	/** Max spread of cast/fired projectiles (degrees). Used to add a random element to bots aiming */
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> ProjectileClass;
	
};
