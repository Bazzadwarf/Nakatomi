// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsUIWidget.h"

#include <Kismet/KismetSystemLibrary.h>

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

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
		ResolutionButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::PlayClickedSound);

		ResolutionButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayHoveredSound);
		ResolutionButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::ResolutionTextBlockHoveredDelegate);
		
		ResolutionButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayUnhoveredSound);
		ResolutionButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::ResolutionTextBlockUnhoveredDelegate);
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
		RefreshRateButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::PlayClickedSound);
		
		RefreshRateButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayHoveredSound);
		RefreshRateButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::RefreshRateTextBlockHoveredDelegate);

		RefreshRateButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayUnhoveredSound);
		RefreshRateButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::RefreshRateTextBlockUnhoveredDelegate);
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
		BackButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::PlayClickedSound);
		
		BackButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayHoveredSound);
		BackButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::BackTextBlockHoveredDelegate);

		BackButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayUnhoveredSound);
		BackButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::BackTextBlockUnhoveredDelegate);
	}

	if (ResetToDefaultsButton)
	{
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::ResetToDefaultsButtonOnClicked);
		ResetToDefaultsButton->OnClicked.AddUniqueDynamic(this, &UOptionsUIWidget::PlayClickedSound);
		
		ResetToDefaultsButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayHoveredSound);
		ResetToDefaultsButton->OnHovered.AddUniqueDynamic(this, &UOptionsUIWidget::ResetToDefaultsTextBlockHoveredDelegate);

		ResetToDefaultsButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::PlayUnhoveredSound);
		ResetToDefaultsButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsUIWidget::ResetToDefaultsTextBlockUnhoveredDelegate);
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}

	SetIsFocusable(true);
}

void UOptionsUIWidget::BackButtonOnClicked()
{
	ReturnToPreviousScreen();
}

void UOptionsUIWidget::ResetToDefaultsButtonOnClicked()
{
	GEngine->GameUserSettings->SetToDefaults(); // :)
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsUIWidget::OnResolutionSelectorChanged()
{
	FIntPoint screenResolution = GEngine->GameUserSettings->GetDesktopResolution();
	//float widthScale = static_cast<float>(screenResolution.X) / static_cast<float>(screenResolution.Y);
	float widthScale = static_cast<float>(1920) / static_cast<float>(1080);

	switch (GEngine->GameUserSettings->GetScreenResolution().Y)
	{
	case 720:
		screenResolution.Y = 1080;
		break;
	case 1080:
		screenResolution.Y = 1440;
		break;
	case 1440:
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

	GEngine->GameUserSettings->ApplySettings(false);
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
		ResolutionButton->SetIsEnabled(false);	
	}
	else
	{
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
		ResolutionButton->SetIsEnabled(true);
	}

	GEngine->GameUserSettings->ApplySettings(false);
	this->PlayHoveredSound();
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
	GEngine->GameUserSettings->ApplySettings(false);
}

void UOptionsUIWidget::OnVsyncCheckboxChanged(bool bIsChecked)
{
	GEngine->GameUserSettings->SetVSyncEnabled(bIsChecked);
	GEngine->GameUserSettings->ApplySettings(false);
	this->PlayHoveredSound();
}

void UOptionsUIWidget::OnDynamicResolutionCheckboxChanged(bool bIsChecked)
{
	GEngine->GameUserSettings->SetDynamicResolutionEnabled(bIsChecked);
	GEngine->GameUserSettings->ApplySettings(false);
	this->PlayHoveredSound();
}
