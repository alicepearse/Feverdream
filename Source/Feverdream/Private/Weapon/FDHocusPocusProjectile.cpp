// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDHocusPocusProjectile.h"
#include "Components/SphereComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "ActionSystem/FDActionComponent.h"
#include "ActionSystem/FDActionEffect.h"
#include "Components/FDAttributeComponent.h"
#include "Framework/FDGameplayFunctionLibrary.h"
#include "Weapon/FDProjectileBase.h"

AFDHocusPocusProjectile::AFDHocusPocusProjectile()
{
	DamageAmount = -20;

	
}

void AFDHocusPocusProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFDHocusPocusProjectile::OnActorOverlap);
}

void AFDHocusPocusProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != GetInstigator()))
	{
// 		UFDAttributeComponent* AttributeComp = Cast<UFDAttributeComponent>(OtherActor->GetComponentByClass(UFDAttributeComponent::StaticClass()));
// 		if (AttributeComp)
// 		{
// 			AttributeComp->ApplyHealthChange(OtherActor, DamageAmount);
// 	
// 			Explode();
// 		}
	
		// Check for Parrying Tag if successful perform parry
		UFDActionComponent* ActionComp = Cast<UFDActionComponent>(OtherActor->GetComponentByClass(UFDActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			// Reverse direction (deflect)
			MovementComp->Velocity = -MovementComp->Velocity;

			// Change instigator to other actor so the projectile will damage the new target actor (original instigator)
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		if (UFDGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();

			if (ActionComp && HasAuthority())
			{
				ActionComp->AddAction(OtherActor, BurningActionClass);
			}
		}
 	}
}

// Called when the game starts or when spawned
void AFDHocusPocusProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFDHocusPocusProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

