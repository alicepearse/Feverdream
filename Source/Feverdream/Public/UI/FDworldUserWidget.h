// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FDworldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDworldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** The actor to which this widget is attached */
	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (ExposeOnSpawn=true))
	AActor* AttachedActor;

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

protected:
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
};
