// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FDMainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class FEVERDREAM_API AFDMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFDMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Scene components
	 */

	/** Spring arm attached to main character to be used with third person perspective camera component */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

// 	/** First person perspective camera component */
// 	UPROPERTY(VisibleAnywhere)
// 	UCameraComponent* FPPCameraComp;

	/** Third person perspective camera component */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TPPCameraComp;

	/**
	 * Character Movement
	 */

	// Move forward function
	void MoveForward(float Value);

	// Move right function
	void MoveRight(float Value);

	/** Called via input to turn at a given rate
	 * @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate.
	 */
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	 * @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate.
	 */
	void LookUpRate(float Rate);

	/** Base turn rate to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/**
	 * Action Input functions
	 */

	 void Casting();

	 /** Projectile class variable needed for casting function */
	 UPROPERTY(EditAnywhere, Category = Casting)
	 TSubclassOf<AActor>ProjectileClass;

	 /** Space to select socket for Casting */
	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Casting)
	 FName CastingSocket;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
