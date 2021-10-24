// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FDProjectileBase.h"
#include "FDHocusPocusProjectile.generated.h"

class UParticleSystem;

UCLASS()
class FEVERDREAM_API AFDHocusPocusProjectile : public AFDProjectileBase
{
	GENERATED_BODY()


protected:
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
