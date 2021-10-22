// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FDReactiveExplosive.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class FEVERDREAM_API AFDReactiveExplosive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDReactiveExplosive();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneComponents)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneComponents)
	URadialForceComponent* RadialForceComp;

	UFUNCTION()
	void OnHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void PostInitializeComponents() override;

};
