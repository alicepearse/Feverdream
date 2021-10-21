// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FDMainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFDMainCharacter::AFDMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	FPPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("1PCameraComp"));
	FPPCameraComp->SetupAttachment(SpringArmComp);

	TPPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("3PCameraComp"));
	TPPCameraComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFDMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFDMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AFDMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

// Called every frame
void AFDMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFDMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFDMainCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &AFDMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

