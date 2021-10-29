// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/FDGameplayFunctionLibrary.h"
#include "Components/FDAttributeComponent.h"

bool UFDGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if (TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor: %s"), *GetNameSafe(TargetActor));
	}
	UFDAttributeComponent* AttributeComp = UFDAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool UFDGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			// Calculate direction (Target - Origin) then normalize so that it is just the direction without magnitude
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
		}

		return true;
	}
	return false;
}
