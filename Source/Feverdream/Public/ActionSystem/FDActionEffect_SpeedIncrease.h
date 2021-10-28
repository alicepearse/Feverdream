// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/FDActionEffect.h"
#include "FDActionEffect_SpeedIncrease.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDActionEffect_SpeedIncrease : public UFDActionEffect
{
	GENERATED_BODY()

public:

	UFDActionEffect_SpeedIncrease();

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Action");
	float SpeedIncrease;

	
};
