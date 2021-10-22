// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FDInteractionComponent.h"
#include "UI/FDGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UFDInteractionComponent::UFDInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFDInteractionComponent::PrimaryInteract()
{

	// Only query objects with collision WorldDynamic
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	// Get line trace start and end location from actor owner's eyes
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLoc = EyeLocation + (EyeRotation.Vector() * 1000);

// 	FHitResult Hit;
// 
// 	// Perform line trace
// 	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLoc, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);


	/** Sphere trace that returns array of multiple objects queried
	 * @param FQuat::Identity This is a default empty rotataion
	 */
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLoc, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green :FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UFDGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IFDGameplayInterface::Execute_Interact(HitActor, MyPawn);

				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}

	DrawDebugLine(GetWorld(), EyeLocation, EndLoc, LineColor, false, 2.0f, 0, 2.0f);

}

