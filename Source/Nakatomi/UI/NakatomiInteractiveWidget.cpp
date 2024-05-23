// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/NakatomiInteractiveWidget.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void UNakatomiInteractiveWidget::PlayHoveredSound()
{
	if (ButtonHoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoveredSound);
	}
}

void UNakatomiInteractiveWidget::SetTextBlockHovered(UTextBlock* TextBlock)
{
	TextBlock->SetColorAndOpacity(FSlateColor(ButtonHoveredTextColor));
}

void UNakatomiInteractiveWidget::SetTextBlockUnhovered(UTextBlock* TextBlock)
{
	TextBlock->SetColorAndOpacity(FSlateColor(ButtonUnhoveredTextColor));
}

void UNakatomiInteractiveWidget::PlayUnhoveredSound()
{
	if (ButtonUnhoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonUnhoveredSound);
	}
}

void UNakatomiInteractiveWidget::PlayClickedSound()
{
	if (ButtonClickedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonUnhoveredSound);
	}
}

void UNakatomiInteractiveWidget::ReturnToPreviousScreen()
{
	// TODO: Implement Functionality
	GEngine->GameUserSettings->ApplySettings(false);

	this->RemoveFromParent();
	PreviousScreen->AddToViewport();
}

void UNakatomiInteractiveWidget::SetReturnScreen(UUserWidget* userWidget)
{
	if (userWidget)
	{
		PreviousScreen = userWidget;
	}
}
