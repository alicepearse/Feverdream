// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/FDActionEffect_SpeedIncrease.h"
#include "Characters/FDMainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UFDActionEffect_SpeedIncrease::UFDActionEffect_SpeedIncrease()
{
	SpeedIncrease = 200.0f;
}

void UFDActionEffect_SpeedIncrease::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	AFDMainCharacter* Player = Cast<AFDMainCharacter>(Instigator);
	if (Player)
	{
		UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(Player->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
		if (MoveComp)
		{
			MoveComp->MaxWalkSpeed -= SpeedIncrease;
			UE_LOG(LogTemp, Warning, TEXT("Speed : %f"), MoveComp->MaxWalkSpeed);
		}
	}

}

void UFDActionEffect_SpeedIncrease::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	AFDMainCharacter* Player = Cast<AFDMainCharacter>(Instigator);
	if (Player)
	{
		UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(Player->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
		if (MoveComp)
		{
			MoveComp->MaxWalkSpeed += SpeedIncrease;
			UE_LOG(LogTemp, Warning, TEXT("Speed : %f"), MoveComp->MaxWalkSpeed);
		}
	}


}


