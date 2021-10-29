// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FDAnimInstance.h"
#include "GameplayTagContainer.h"
#include "ActionSystem/FDActionComponent.h"

void UFDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	if (OwningActor)
	{
		ActionComp = Cast<UFDActionComponent>(OwningActor->GetComponentByClass(UFDActionComponent::StaticClass()));
	}

}

void UFDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");

	if (ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
	}
}
