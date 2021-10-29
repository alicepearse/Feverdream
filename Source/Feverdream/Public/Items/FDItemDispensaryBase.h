// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/FDGameplayInterface.h"
#include "FDItemDispensaryBase.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class FEVERDREAM_API AFDItemDispensaryBase : public AActor, public IFDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDItemDispensaryBase();

protected:

	/**
	 * Scene Components
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DispensaryMeshBase;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* DispenseEffect;

	UPROPERTY(EditAnywhere, Category = "Items")
	TSubclassOf<AActor> DispensedItemsClass;

	UPROPERTY(VisibleAnywhere, Category = "Items")
	AActor* DispensedItems;

	FTimerHandle TimerHandle_ReactivateDispensary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDispensaryActivated;

	/** The time for which the dispensary must remain deactivated after interaction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeactivationTime;

	virtual void DeactivateDispensary();

	virtual void ReactivateDispensary();

	virtual void SetDispensaryState(bool bNewIsActivated);

public:	

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	/**
	 * UI
	 */

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn);

};
