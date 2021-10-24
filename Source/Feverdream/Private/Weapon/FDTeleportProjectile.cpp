// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDTeleportProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/FDProjectileBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"

void AFDTeleportProjectile::Teleport()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		TeleportLocation = GetActorLocation();

		// Make sure we always spawn upright in the direction of the projectile
		float ProjectileDirection = GetActorRotation().Roll;
		TeleportRotation = FRotator(0.0f, 0.0f, ProjectileDirection);

		ActorToTeleport->TeleportTo(TeleportLocation, TeleportRotation);
	}

	Destroy();
}

void AFDTeleportProjectile::SelfDissipate()
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	}

	MovementEffectComp->DeactivateSystem();
	MovementComp->StopMovementImmediately();

 	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AFDTeleportProjectile::Teleport, 0.2f);	
}

void AFDTeleportProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	}

	TeleportLocation = GetActorLocation();

	// Make sure we always spawn upright the direction of the projectile
	TeleportRotation = GetActorRotation();
	TeleportRotation.Pitch = 0.0f;
	TeleportRotation.Roll = 0.0f;

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AFDTeleportProjectile::Teleport, 0.2f);

	MovementEffectComp->DestroyComponent(false);
}

void AFDTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_Lifetime, this, &AFDTeleportProjectile::SelfDissipate, Lifespan);
}

