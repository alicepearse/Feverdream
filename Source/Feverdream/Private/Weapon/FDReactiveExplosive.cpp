// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDReactiveExplosive.h"

#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AFDReactiveExplosive::AFDReactiveExplosive()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetMassOverrideInKg(NAME_None, 100.0f, true);
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->Radius = 800.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
}

void AFDReactiveExplosive::OnHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}

void AFDReactiveExplosive::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &AFDReactiveExplosive::OnHitExplode);
}


