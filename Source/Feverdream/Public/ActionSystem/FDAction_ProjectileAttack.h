// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/FDAction.h"
#include "FDAction_ProjectileAttack.generated.h"

class UAnimMontage;
class UParticleSystem;


/**
 * 
 */
UCLASS()
class FEVERDREAM_API UFDAction_ProjectileAttack : public UFDAction
{
	GENERATED_BODY()

public:

	UFDAction_ProjectileAttack();

protected:

	/** Projectile class variable needed for casting function */
	UPROPERTY(EditAnywhere, Category = "Casting")
	TSubclassOf<AActor>ProjectileClass;

	/** Space to select socket for Casting */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Casting")
	FName CastingSocketName;

	/** Casting Animation Montage */
	UPROPERTY(EditAnywhere, Category = "Casting")
	UAnimMontage* CastingAnim;

	/** Casting Animation Delay */
	UPROPERTY(EditAnywhere, Category = "Casting")
	float CastingAnimDelay;

	/** Particle system played during Casting Animation  */
	UPROPERTY(EditAnywhere, Category = "Casting")
	UParticleSystem* CastingFX;

	UFUNCTION()
	void CastingDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

};
