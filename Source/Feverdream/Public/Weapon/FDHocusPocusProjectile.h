// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/FDProjectileBase.h"
#include "FDHocusPocusProjectile.generated.h"

class UParticleSystem;


UCLASS()
class FEVERDREAM_API AFDHocusPocusProjectile : public AFDProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDHocusPocusProjectile();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
