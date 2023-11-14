// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUIWidget.h"

void UMainMenuUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::NewGameButtonOnClicked);
	}

	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::LoadGameButtonOnClicked);
	}
	
	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::OptionsButtonOnClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUIWidget::QuitButtonOnClicked);
	}
}

void UMainMenuUIWidget::NewGameButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UMainMenuUIWidget::LoadGameButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UMainMenuUIWidget::OptionsButtonOnClicked()
{
	if (OptionsMenuWidget)
	{
		currentOptionsMenuWidget = CreateWidget<UOptionsUIWidget>(GetWorld(), OptionsMenuWidget);
		currentOptionsMenuWidget->AddToViewport();
		currentOptionsMenuWidget->SetReturnScreen(this);
		this->RemoveFromParent();
	}
}

void UMainMenuUIWidget::QuitButtonOnClicked()
{
	// TODO: We probably want to do an autosave here.

	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}
