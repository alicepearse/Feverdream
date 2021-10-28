// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDAction_ProjectileAttack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UFDAction_ProjectileAttack::UFDAction_ProjectileAttack()
{
	// Initialize casting variables
	CastingSocketName = "CastingSocket";
	CastingAnimDelay = 0.5f;
}

void UFDAction_ProjectileAttack::CastingDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensure(ProjectileClass))
	{
		// Find the location of the point from which to perform casting projectile
		FVector CastingLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(CastingSocketName);

		// Trace shape
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Instigator
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(InstigatorCharacter);

		// Only query objects with collision WorldDynamic and WorldStatic
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		// Find where the target viewpoint is
		FVector ViewLocation = InstigatorCharacter->GetPawnViewLocation();
		FVector TargetViewPoint = ViewLocation + (InstigatorCharacter->GetControlRotation().Vector() * 1000);

		// Find which objects will be hit between the camera and the camera target viewpoint
		FHitResult Hit;

		bool bSuccessfulHit = GetWorld()->SweepSingleByObjectType(Hit, ViewLocation, TargetViewPoint, FQuat::Identity, ObjectQueryParams, Shape, QueryParams);

		// Decide which location will be used for impact
		FVector ImpactLocation;

		// If no objects were hit then use TargetViewPoint as impact location
		ImpactLocation = TargetViewPoint;

		if (bSuccessfulHit)
		{
			ImpactLocation = Hit.ImpactPoint;
		}

		// Calculate projectile spawn rotation
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(ImpactLocation - CastingLocation).Rotator();

		// Spawn projectile
		FTransform SpawnTransform = FTransform(ProjectileRotation, CastingLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);

		// 		DrawDebugSphere(GetWorld(), ImpactLocation, 30.0f, 32, FColor::Green, false, 2.0f);
	}

	StopAction(InstigatorCharacter);
}

void UFDAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(CastingAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingFX, Character->GetMesh(), CastingSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		if (Character->HasAuthority())
		{
			FTimerHandle TimerHandle_CastingDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "CastingDelay_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_CastingDelay, Delegate, CastingAnimDelay, false);
		}
	}
}

void UFDAction_ProjectileAttack::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);



}

