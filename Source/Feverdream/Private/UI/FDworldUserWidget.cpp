// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FDworldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"

void UFDworldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();

		UE_LOG(LogTemp, Warning, TEXT("Attatched actor no longer valid, removing health widget"));

		return;
	}

	FVector2D ScreenPosition;
	FVector DesiredWidgetLocation = AttachedActor->GetActorLocation() + WorldOffset;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), DesiredWidgetLocation, ScreenPosition);
	if (bIsOnScreen)
	{
		// Rescale the widget position to the current screen size
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}

	if (ParentSizeBox)
	{
		ParentSizeBox ->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}
