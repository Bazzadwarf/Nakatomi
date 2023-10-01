// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseUIWidget.h"


void UPauseUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::ResumeButtonOnClicked);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::OptionsButtonOnClicked);
	SaveButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::SaveButtonOnClicked);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::QuitButtonOnClicked);
	CloseApplicationButton->OnClicked.AddUniqueDynamic(this, &UPauseUIWidget::CloseApplicationButtonOnClicked);
}

void UPauseUIWidget::ResumeButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UPauseUIWidget::OptionsButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UPauseUIWidget::SaveButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UPauseUIWidget::QuitButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UPauseUIWidget::CloseApplicationButtonOnClicked()
{
	// TODO: Implement Functionality
}
