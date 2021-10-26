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

	virtual void DeactivateDispensary() override;

	virtual void ReactivateDispensary() override;

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
