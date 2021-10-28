// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FDBreakableObjectBase.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UFDAttributeComponent;

UCLASS()
class FEVERDREAM_API AFDBreakableObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDBreakableObjectBase();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* BreakEffect;

	UPROPERTY(VisibleAnywhere)
	UFDAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UFDAttributeComponent* OwningComp, float NewHealth, float Delta);

};
