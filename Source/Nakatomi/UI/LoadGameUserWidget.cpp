// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/LoadGameUserWidget.h"

void ULoadGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonOnClicked);
		CancelButton->OnClicked.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayClickedSound);

		CancelButton->OnHovered.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonHoveredDelegate);
		CancelButton->OnHovered.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayHoveredSound);

		CancelButton->OnUnhovered.AddUniqueDynamic(this, &ULoadGameUserWidget::CancelButtonUnhoveredDelegate);
		CancelButton->OnUnhovered.AddUniqueDynamic(this, &ULoadGameUserWidget::PlayUnhoveredSound);
	}
}

void ULoadGameUserWidget::CancelButtonOnClicked()
{
	ReturnToPreviousScreen();
}
