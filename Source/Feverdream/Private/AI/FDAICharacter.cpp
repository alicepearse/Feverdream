// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FDAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/FDAttributeComponent.h"
#include "BrainComponent.h"
#include "UI/FDworldUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "ActionSystem/FDActionComponent.h"

// Sets default values
AFDAICharacter::AFDAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	AttributeComp = CreateDefaultSubobject<UFDAttributeComponent>(TEXT("AttributeComp"));
	
	ActionComp = CreateDefaultSubobject<UFDActionComponent>(TEXT("ActionComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

// 	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);

	TimeToHitParameter = "TimeToHit";

}

void AFDAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFDAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &AFDAICharacter::OnHealthChanged);
}

void AFDAICharacter::SetTargetActor(AActor* NewTargetActor)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", NewTargetActor);
	}
}

void AFDAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), TEXT("Player Spotted"), nullptr, FColor::White, 4.0f, true);
}

void AFDAICharacter::OnHealthChanged(AActor* InstigatorActor, UFDAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Cause the character's material to flash when hit
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParameter, GetWorld()->TimeSeconds);

		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		// Create and show health bar
		if (ActiveHealthBar == nullptr)
		{
			if (ensure(AIHealthWidgetClass))
			{
				ActiveHealthBar = CreateWidget<UFDworldUserWidget>(GetWorld(), AIHealthWidgetClass);
				if (ActiveHealthBar)
				{
					ActiveHealthBar->AttachedActor = this;
					ActiveHealthBar->AddToViewport();
				}
			}
		}

		// Check if player has died
		if (NewHealth <= 0.0f && Delta < 0.0f)
		{

			// Stop behaviorTree
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			// Ragdoll on death
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()-> DisableMovement();

			// Set Lifespan
			SetLifeSpan(10.0f);
		}
	}

}



