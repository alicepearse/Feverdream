// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "FDAction.generated.h"

class UWorld;
class UFDActionComponent;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;

};

/**
 * 
 */
UCLASS(Blueprintable)
class FEVERDREAM_API UFDAction : public UObject
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(Replicated)
	UFDActionComponent* ActionComponent;

	/** Tags applied to owning actor for the duration of the activated action */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	/** Will block any action with these tags applied to owning actor */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlocksTags;

	UPROPERTY(ReplicatedUsing = "OnRep_RepData")
	FActionRepData RepData;
// 	bool bIsRunning;

public:
	
	void Initialize(UFDActionComponent* NewActionComp);

	/** Start immediately when added to an action component */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StopAction(AActor* Instigator);

	/** A that can be used to start/stop the action without a reference to the object */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning();

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

protected:

	UFUNCTION()
	void OnRep_RepData();

	UFUNCTION(BlueprintCallable, Category = "Tags")
	UFDActionComponent* GetOwningComponent() const;
};
