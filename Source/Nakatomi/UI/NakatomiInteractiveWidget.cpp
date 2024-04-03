// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/NakatomiInteractiveWidget.h"

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
