// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/FDItemDispensaryBase.h"
#include "FDVendingDispensary.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDVendingDispensary : public AFDItemDispensaryBase
{
	GENERATED_BODY()

public:

	AFDVendingDispensary();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 CreditCost;

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
