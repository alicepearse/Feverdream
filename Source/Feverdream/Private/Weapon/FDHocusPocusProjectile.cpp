// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDHocusPocusProjectile.h"
#include "Components/FDAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Weapon/FDProjectileBase.h"

void AFDHocusPocusProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFDHocusPocusProjectile::OnActorOverlap);
}

void AFDHocusPocusProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UFDAttributeComponent* AttributeComp = Cast<UFDAttributeComponent>(OtherActor->GetComponentByClass(UFDAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
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

