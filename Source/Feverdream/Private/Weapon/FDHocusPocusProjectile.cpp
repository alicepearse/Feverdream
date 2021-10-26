// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDHocusPocusProjectile.h"
#include "Components/FDAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Weapon/FDProjectileBase.h"
#include "Framework/FDGameplayFunctionLibrary.h"

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

		if (UFDGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			UE_LOG(LogTemp, Warning, TEXT("Apply directional damage called"));

			Explode();
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

