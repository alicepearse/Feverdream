// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FDTeleportProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/FDProjectileBase.h"
#include "Particles/ParticleSystemComponent.h"

void AFDTeleportProjectile::Teleport()
{
	UE_LOG(LogTemp, Warning, TEXT("Teleport called"));
	AActor* TempInst = GetInstigator();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *TempInst->GetName());

	GetInstigator()->TeleportTo(TeleportLocation, TeleportRotation);

	Destroy();
}

void AFDTeleportProjectile::SelfDissipate()
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

void AFDTeleportProjectile::OnProjectileHitExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

