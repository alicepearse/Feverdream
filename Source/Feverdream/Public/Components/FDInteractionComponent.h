// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FDInteractionComponent.generated.h"

class UFDworldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FEVERDREAM_API UFDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFDInteractionComponent();

protected:

	void FindBestInteractable();

	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> InteractCollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UFDworldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UFDworldUserWidget* DefaultWidgetInstance;


public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PrimaryInteract();

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocusActor);
};
