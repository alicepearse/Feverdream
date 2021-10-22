// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FDProjectileBase.h"
#include "FDTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FEVERDREAM_API AFDTeleportProjectile : public AFDProjectileBase
{
	GENERATED_BODY()

protected:

	FVector TeleportLocation;

	FRotator TeleportRotation;

	FTimerHandle TimerHandle_Teleport;

	void Teleport();

	void SelfDissipate();

	virtual void OnProjectileHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
