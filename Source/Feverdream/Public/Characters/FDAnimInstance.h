// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FDAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	/** Is pawn stunned based on GameplayTag Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsStunned;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UFDActionComponent* ActionComp;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
