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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
