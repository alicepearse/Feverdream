// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FDAttributeComponent.h"

// Sets default values for this component's properties
UFDAttributeComponent::UFDAttributeComponent()
{
	// Set default variables
	Health = 100.0f;
	MaxHealth = 100.0f;
}

bool UFDAttributeComponent::bIsAlive() const
{
	return Health > 0.0f;
}

float UFDAttributeComponent::GetHealth()
{
	return Health;
}

float UFDAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

bool UFDAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	float ClampedHealth = FMath::Clamp(Health, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, ClampedHealth, MaxHealth, Delta);

	return true;
}

