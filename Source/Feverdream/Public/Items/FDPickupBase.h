// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/FDGameplayInterface.h"
#include "FDPickupBase.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class FEVERDREAM_API AFDPickupBase : public AActor, public IFDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDPickupBase();

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* MeshEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* PickupEffect;

	UFUNCTION()
	void PickUp();

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;


};
