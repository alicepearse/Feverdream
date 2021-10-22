// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFDProjectileBase::AFDProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	MovementEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	MovementEffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	// Initial Values
	Lifespan = 5.0f;
}

void AFDProjectileBase::OnProjectileHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	Destroy();
}



void AFDProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &AFDProjectileBase::OnProjectileHitExplode);
}

// Called every frame
void AFDProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

