// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsUIWidget.h"

#include <Kismet/KismetSystemLibrary.h>

#include "GameFramework/GameUserSettings.h"

void UOptionsUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResolutionButton)
	{
		if (ResolutionTextBlock)
		{
			ResolutionTextBlock->SetText(FText::AsNumber(GEngine->GameUserSettings->GetScreenResolution().Y));
		}

		ResolutionButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::OnResolutionSelectorChanged);
	}

	if (FullscreenCheckBox)
	{
		FullscreenCheckBox->SetCheckedState(GEngine->GameUserSettings->GetFullscreenMode() == EWindowMode::Fullscreen
			                                    ? ECheckBoxState::Checked
			                                    : ECheckBoxState::Unchecked);

		FullscreenCheckBox->OnCheckStateChanged.AddUniqueDynamic(
			this, &UOptionsUIWidget::OnFullscreenCheckboxChanged);
	}

	if (RefreshRateButton)
	{
		if (RefreshRateTextBlock)
		{
			SetRefreshRateTextBlock(GEngine->GameUserSettings->GetFrameRateLimit());
		}

		RefreshRateButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::OnRefreshRateSelectorChanged);
	}
	
	if (VsyncCheckBox)
	{
		VsyncCheckBox->SetCheckedState(GEngine->GameUserSettings->IsVSyncEnabled()
			                               ? ECheckBoxState::Checked
			                               : ECheckBoxState::Unchecked);

		VsyncCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UOptionsUIWidget::OnVsyncCheckboxChanged);
	}

	if (DynamicResolutionCheckBox)
	{
		DynamicResolutionCheckBox->SetCheckedState(GEngine->GameUserSettings->IsDynamicResolutionEnabled()
			                                           ? ECheckBoxState::Checked
			                                           : ECheckBoxState::Unchecked);

		DynamicResolutionCheckBox->OnCheckStateChanged.AddUniqueDynamic(
			this, &UOptionsUIWidget::OnDynamicResolutionCheckboxChanged);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::BackButtonOnClicked);
	}

	if (ResetToDefaultsButton)
	{
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::ResetToDefaultsButtonOnClicked);
	}
}

void UOptionsUIWidget::SetReturnScreen(UUserWidget* userWidget)
{
	if (userWidget)
	{
		PreviousScreen = userWidget;
	}
}

void UOptionsUIWidget::BackButtonOnClicked()
{
	// TODO: Implement Functionality
	GEngine->GameUserSettings->ApplySettings(true);

	this->RemoveFromParent();
	PreviousScreen->AddToViewport();
}

void UOptionsUIWidget::ResetToDefaultsButtonOnClicked()
{
	GEngine->GameUserSettings->SetToDefaults(); // :)
	GEngine->GameUserSettings->ApplySettings(true);
}

void UOptionsUIWidget::OnResolutionSelectorChanged()
{
	FIntPoint screenResolution = GEngine->GameUserSettings->GetDesktopResolution();
	float widthScale = static_cast<float>(screenResolution.X) / static_cast<float>(screenResolution.Y);

	switch (GEngine->GameUserSettings->GetScreenResolution().Y)
	{
	case 720:
		screenResolution.Y = 1080;
		break;
	case 1080:
		screenResolution.Y = 1440;
		break;
	case 1440:
		screenResolution.Y = 2160;
		break;
	case 2160:
		screenResolution.Y = 720;
		break;
	default:
		screenResolution.Y = 1080;
	}
	
	screenResolution.X = widthScale * screenResolution.Y;
	GEngine->GameUserSettings->SetScreenResolution(screenResolution);
	

	if (ResolutionTextBlock)
	{
		ResolutionTextBlock->SetText(FText::AsNumber(screenResolution.Y));
	}

	GEngine->GameUserSettings->ApplySettings(true);
}

void UOptionsUIWidget::SetRefreshRateTextBlock(float RefreshRateText)
{
	RefreshRateTextBlock->SetText(RefreshRateText == 0.0f ? FText::FromString("Unlimited") : FText::AsNumber(RefreshRateText));
}

void UOptionsUIWidget::OnFullscreenCheckboxChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}
	else
	{
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	}

	GEngine->GameUserSettings->ApplySettings(true);
}

void UOptionsUIWidget::OnRefreshRateSelectorChanged()
{
	switch (static_cast<int>(GEngine->GameUserSettings->GetFrameRateLimit()))
	{
	case 0:
		GEngine->GameUserSettings->SetFrameRateLimit(60);
		break;
	case 60:
		GEngine->GameUserSettings->SetFrameRateLimit(144);
		break;
	case 144:
		GEngine->GameUserSettings->SetFrameRateLimit(240);
		break;
	case 240:
		GEngine->GameUserSettings->SetFrameRateLimit(0);
		break;
	default:
		GEngine->GameUserSettings->SetFrameRateLimit(0);
	}
	
	SetRefreshRateTextBlock(GEngine->GameUserSettings->GetFrameRateLimit());
	GEngine->GameUserSettings->ApplySettings(true);
}

void UOptionsUIWidget::OnVsyncCheckboxChanged(bool bIsChecked)
{
	GEngine->GameUserSettings->SetVSyncEnabled(bIsChecked);
	GEngine->GameUserSettings->ApplySettings(true);
}

void UOptionsUIWidget::OnDynamicResolutionCheckboxChanged(bool bIsChecked)
{
	GEngine->GameUserSettings->SetDynamicResolutionEnabled(bIsChecked);
	GEngine->GameUserSettings->ApplySettings(true);
}
