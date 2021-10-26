// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FDAttributeComponent.h"
#include "Framework/FDGameModeBase.h"

static TAutoConsoleVariable<float>CVarDamageMultiplier(TEXT("fd.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UFDAttributeComponent::UFDAttributeComponent()
{
	// Set default variables
	Health = 100.0f;
	MaxHealth = 100.0f;
}

UFDAttributeComponent* UFDAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UFDAttributeComponent>(FromActor->GetComponentByClass(UFDAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UFDAttributeComponent::IsActorAlive(AActor* FromActor)
{
	UFDAttributeComponent* AttributeComp = GetAttributes(FromActor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

bool UFDAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UFDAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}

float UFDAttributeComponent::GetHealth()
{
	return Health;
}

float UFDAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

bool UFDAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	// Check for God Mode
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f) 
	{
		return false;
	}

	// Check if damage is being done and apply multiplier if damage multiplier is active
	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;

	Health += Delta;

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, MaxHealth, ActualDelta);

	// Died
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		AFDGameModeBase* GM = GetWorld()->GetAuthGameMode<AFDGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0.0f;
}

