// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FDProjectileBase.h"
#include "GameplayTagContainer.h"
#include "FDHocusPocusProjectile.generated.h"

class UParticleSystem;
class UFDActionEffect;

UCLASS()
class FEVERDREAM_API AFDHocusPocusProjectile : public AFDProjectileBase
{
	GENERATED_BODY()

public:
	
	AFDHocusPocusProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UFDActionEffect> BurningActionClass;
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
