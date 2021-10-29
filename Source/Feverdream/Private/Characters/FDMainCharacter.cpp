// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FDMainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Components/FDInteractionComponent.h"
#include <DrawDebugHelpers.h>
#include "Components/FDAttributeComponent.h"
#include "ActionSystem/FDActionComponent.h"

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

	ActiveCamera = TPPCameraComp;

	InteractionComp = CreateDefaultSubobject<UFDInteractionComponent>(TEXT("InteractionComp"));

	AttributeComp = CreateDefaultSubobject<UFDAttributeComponent>(TEXT("AttributeComp"));

	ActionComp = CreateDefaultSubobject<UFDActionComponent>(TEXT("ActionComp"));

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

	// Initialize casting variables
	CastingSocketName = "CastingSocket";
	CastingAnimDelay = 0.5f;
}

void AFDMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AFDMainCharacter::OnHealthChanged);
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
// 	CalculateAim();
// 
// 	PlayAnimMontage(CastingAnim);
// 
// 	GetWorldTimerManager().SetTimer(TimerHandle_Casting, this, &AFDMainCharacter::Casting_TimeElapsed, CastingAnimDelay);

	ActionComp->StartActionByName(this, "Casting");
}

void AFDMainCharacter::CalculateAim()
{
	// Find where the camera target viewpoint is
	FMinimalViewInfo CameraPerspective;
	ActiveCamera->GetCameraView(0.0f, CameraPerspective);
	CameraLocation = CameraPerspective.Location;
	FRotator CameraRotation = CameraPerspective.Rotation;
	TargetViewPoint = CameraLocation + (CameraRotation.Vector() * 1000);

// 	DrawDebugLine(GetWorld(), CameraLocation, TargetViewPoint, FColor::Red, false, 2.0f, 0, 2.0f);
}

void AFDMainCharacter::Casting_TimeElapsed()
{
	// Find the location of the point from which to perform casting projectile
	FVector CastingLocation = GetMesh()->GetSocketLocation(CastingSocketName);

	// Only query objects with collision WorldDynamic and WorldStatic
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);	
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	// Find which objects will be hit between the camera and the camera target viewpoint
	TArray<FHitResult> ObjectsInSight;
	bool bSuccessfulHit = GetWorld()->LineTraceMultiByObjectType(ObjectsInSight, CameraLocation, TargetViewPoint, ObjectQueryParams);

	// Decide which location will be used for impact
	FVector ImpactLocation;

	if (bSuccessfulHit)
	{
		for (FHitResult ObjectInSight : ObjectsInSight)
		{
			ImpactLocation = ObjectInSight.Location;
			return;
		}
	}
	else
	{
		// if no objects were hit then use TargetViewPoint as impact location
		ImpactLocation = TargetViewPoint;
	}

	// Calculate projectile spawn rotation
	FRotator ProjectileRotation = (ImpactLocation - CastingLocation).Rotation();

	// Spawn projectile
	FTransform SpawnTransform = FTransform(ProjectileRotation, CastingLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	if (ensure(ProjectileClass != nullptr))
	{
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
// 		DrawDebugSphere(GetWorld(), ImpactLocation, 30.0f, 32, FColor::Green, false, 2.0f);
	}
}

void AFDMainCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}

}

void AFDMainCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AFDMainCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

FVector AFDMainCharacter::GetPawnViewLocation() const
{
	return ActiveCamera->GetComponentLocation();
}

void AFDMainCharacter::OnHealthChanged(AActor* InstigatorActor, UFDAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Cause the character's material to flash when hit
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	// Check if player has died
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

		SetLifeSpan(5.0f);
	}
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
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AFDMainCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFDMainCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFDMainCharacter::SprintStop);
}

void AFDMainCharacter::HealSelf(float Amount /*= 100.0f*/)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

