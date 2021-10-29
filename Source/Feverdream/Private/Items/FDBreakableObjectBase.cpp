// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FDBreakableObjectBase.h"
#include "Components//StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/FDAttributeComponent.h"

// Sets default values
AFDBreakableObjectBase::AFDBreakableObjectBase()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BreakEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BreakEffect"));
	BreakEffect->SetupAttachment(MeshComp);

	AttributeComp = CreateDefaultSubobject<UFDAttributeComponent>(TEXT("AttributeComp"));
	AttributeComp->OnHealthChanged.AddDynamic(this, &AFDBreakableObjectBase::OnHealthChanged);


}

void AFDBreakableObjectBase::OnHealthChanged(AActor* InstigatorActor, UFDAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

}



