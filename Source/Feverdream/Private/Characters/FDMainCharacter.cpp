// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FDMainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/CharacterMovementComponent.h"

// Sets default values
AFDMainCharacter::AFDMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

// 	FPPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("1PCameraComp"));
// 	FPPCameraComp->SetupAttachment(RootComponent);

	TPPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("3PCameraComp"));
	TPPCameraComp->SetupAttachment(SpringArmComp);

	// Don't rotate when the camera rotates
	// Let that just affect the camera
	bUseControllerRotationPitch = false;
//	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // ...at this rotation rate.

	// Set turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
}

// Called when the game starts or when spawned
void AFDMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AFDMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		AddMovementInput(GetActorForwardVector(), Value);

// 		// Find out which way is forward
// 		FRotator Rotation = Controller->GetControlRotation();
// 		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
// 
// 		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 		AddMovementInput(Direction, Value);
	}
}

void AFDMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		AddMovementInput(GetActorRightVector(), Value);

// 		// Find which way is right
// 		FRotator Rotation = Controller->GetControlRotation();
// 		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
// 
// 		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 		AddMovementInput(Direction, Value);
	}


}

void AFDMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFDMainCharacter::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFDMainCharacter::Casting()
{
	// Spawn projectile

	FVector CastingLocation = GetMesh()->GetSocketLocation(CastingSocket);
	FTransform SpawnTransform = FTransform(GetControlRotation(), CastingLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ensure(ProjectileClass!=nullptr);

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
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
	PlayerInputComponent->BindAxis("TurnRate", this, &AFDMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFDMainCharacter::LookUpRate);

	PlayerInputComponent->BindAction("Casting", IE_Pressed, this, &AFDMainCharacter::Casting);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

