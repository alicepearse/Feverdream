// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/FDGameplayInterface.h"
#include "FDItemChest.generated.h"

UCLASS()
class FEVERDREAM_API AFDItemChest : public AActor, public IFDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFDItemChest();

protected:
	
	/**
	 * Scene Components
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestBaseInterior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestLid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestLidInterior;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

	/** The target pitch value for the open lid animation of the chest */
	UPROPERTY(EditAnywhere)
	float TargetPitchOpenLid;

};
