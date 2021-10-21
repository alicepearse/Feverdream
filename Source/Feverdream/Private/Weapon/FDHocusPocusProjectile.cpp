// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDHocusPocusProjectile.h"

#include "Components/SphereComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFDHocusPocusProjectile::AFDHocusPocusProjectile()
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
}

void AFDHocusPocusProjectile::OnProjectileHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	Destroy();
}

// Called when the game starts or when spawned
void AFDHocusPocusProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &AFDHocusPocusProjectile::OnProjectileHitExplode);
	
}

// Called every frame
void AFDHocusPocusProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

