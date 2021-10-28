// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FDInteractionComponent.h"
#include "UI/FDGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "UI/FDworldUserWidget.h"

static TAutoConsoleVariable<bool>CVarDebugDrawInteraction(TEXT("fd.DebugDrawInteraction"), false, TEXT("Enable draw debug for interaction component."), ECVF_Cheat);


UFDInteractionComponent::UFDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Set defaults
	TraceDistance = 500.0f;
	TraceRadius = 30.f;
	InteractCollisionChannel = ECC_WorldDynamic;
}


void UFDInteractionComponent::FindBestInteractable()
{
	// ***Debug - for setting debug on or off 
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	// Only query objects with collision WorldDynamic
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(InteractCollisionChannel);

	// Get line trace start and end location from actor owner's eyes
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLoc = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	// 	FHitResult Hit;
	// 
	// 	// Perform line trace
	// 	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLoc, ObjectQueryParams);

	TArray<FHitResult> Hits;

	// Set trace shape
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);


	/** Sphere trace that returns array of multiple objects queried
	 * @param FQuat::Identity This is a default empty rotataion
	 */
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLoc, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Clear focused actor before trying to fill it
	FocusedActor = nullptr;

	// Find actor on which focus is most likely
	for (FHitResult Hit : Hits)
	{
		//**Debug - draw sphere on successful interaction
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 2.0f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UFDGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	// If focusing on actor, show interaction card for that actor
	if (FocusedActor)
	{
		if (DefaultWidgetInstance == nullptr && DefaultWidgetClass)
		{
			DefaultWidgetInstance = CreateWidget<UFDworldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	

	//**Debug - draw line on interact performed
	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, EndLoc, LineColor, false, 2.0f, 0, 2.0f);
	}
}

void UFDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UFDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
	


}

void UFDInteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusedActor);
}

void UFDInteractionComponent::ServerInteract_Implementation(AActor* InFocusActor)
{
	if (InFocusActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No focus actor to interact");
		return;
	}

	APawn* MyPawn = Cast<APawn>(GetOwner());

	IFDGameplayInterface::Execute_Interact(InFocusActor, MyPawn);
}

