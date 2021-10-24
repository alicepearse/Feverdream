// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/FDItemDispensaryBase.h"
#include "FDGumballDispensary.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDGumballDispensary : public AFDItemDispensaryBase
{
	GENERATED_BODY()

public:
	
	AFDGumballDispensary();

protected:

	/**
	 * Scene Components
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GlassMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* GlassMeshBroken;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* GlassMeshUnbroken;

	FTimerHandle TimerHandle_ReactivateDispensary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDispensaryActivated;

	/** The time for which the dispensary must remain deactivated after interaction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeactivationTime;

	void DeactivateDispensary();

	void ReactivateDispensary();

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
