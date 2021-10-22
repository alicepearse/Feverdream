// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FDMainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFDInteractionComponent;
class UAnimMontage;

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

	/** Used to keep track of which camera is active FPP/TPP */
	UCameraComponent* ActiveCamera;

	/** Interaction component for interacting with objects */
	UPROPERTY(VisibleAnywhere)
	UFDInteractionComponent* InteractionComp;

protected:

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

	/** Base look up rate to scale look up functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;


protected:

	/**
	 * Action Input functions
	 */

	void Casting();

	/** Projectile class variable needed for casting function */
	UPROPERTY(EditAnywhere, Category = "Casting")
	TSubclassOf<AActor>ProjectileClass;
	
	/** Space to select socket for Casting */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Casting")
	FName CastingSocket;

	/** Casting Animation Montage */
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* CastingAnim;

	/** Timer for Casting Animation */
	FTimerHandle TimerHandle_Casting;

	/** Stores the camera location at aim - used to calculate an accurate aim target */
	FVector CameraLocation;

	/** Stores the target aim point of the player from their camera perspective */
	FVector TargetViewPoint;

	// used to calculate where the player is aiming
	void CalculateAim();

	// Function called by timer to execute casting
	void Casting_TimeElapsed();

	void PrimaryInteract();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
