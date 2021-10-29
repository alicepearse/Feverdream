// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FDAttributeComponent.h"
#include "Framework/FDGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float>CVarDamageMultiplier(TEXT("fd.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

UFDAttributeComponent::UFDAttributeComponent()
{
	// Set default variables
	Health = 100.0f;
	MaxHealth = 100.0f;

	// Networking
	SetIsReplicatedByDefault(true);
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
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);
	float ActualDelta = NewHealth - OldHealth;

	// [Server]
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		// Died
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			AFDGameModeBase* GM = GetWorld()->GetAuthGameMode<AFDGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return ActualDelta != 0.0f;
}

void UFDAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void UFDAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UFDAttributeComponent, Health);
	DOREPLIFETIME(UFDAttributeComponent, MaxHealth);

}
