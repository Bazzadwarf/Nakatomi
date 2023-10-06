// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsUIWidget.h"

#include "GameFramework/GameUserSettings.h"

void UOptionsUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::ApplyButtonOnClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::BackButtonOnClicked);
	}

	if (ResetToDefaultsButton)
	{
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::ResetToDefaultsButtonOnClicked);
	}

	if (FullscreenBox)
	{
		switch (GEngine->GameUserSettings->GetFullscreenMode())
		{
		case EWindowMode::Fullscreen:
			FullscreenBox->SetCheckedState(ECheckBoxState::Checked);
			break;
		case EWindowMode::WindowedFullscreen:
			FullscreenBox->SetCheckedState(ECheckBoxState::Unchecked);
			break;
		case EWindowMode::Windowed:
			FullscreenBox->SetCheckedState(ECheckBoxState::Unchecked);
			break;
		case EWindowMode::NumWindowModes:
			FullscreenBox->SetCheckedState(ECheckBoxState::Unchecked);
			break;
		default:
			FullscreenBox->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}

void UOptionsUIWidget::ApplyButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UOptionsUIWidget::BackButtonOnClicked()
{
	// TODO: Implement Functionality
}

void UOptionsUIWidget::ResetToDefaultsButtonOnClicked()
{
	// TODO: Implement Functionality

	GEngine->GameUserSettings->SetToDefaults(); // :)
}
