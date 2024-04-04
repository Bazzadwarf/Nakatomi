// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/NakatomiInteractiveWidget.h"
#include "OptionsUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UOptionsUIWidget : public UNakatomiInteractiveWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResolutionButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResolutionTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* FullscreenCheckBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* VsyncCheckBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RefreshRateButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RefreshRateTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* DynamicResolutionCheckBox;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* BackTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetToDefaultsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResetToDefaultsTextBlock;

private:

	UUserWidget* PreviousScreen;
	
public:
	virtual void NativeConstruct() override;

	void SetReturnScreen(UUserWidget* userWidget);
	
private:

	UFUNCTION()
	void BackButtonOnClicked();
	
	UFUNCTION()
	void ResetToDefaultsButtonOnClicked();

	UFUNCTION()
	void OnResolutionSelectorChanged();

	UFUNCTION()
	void SetRefreshRateTextBlock(float RefreshRateText);
	
	UFUNCTION()
	void OnFullscreenCheckboxChanged(bool bIsChecked);

	UFUNCTION()
	void OnRefreshRateSelectorChanged();
	
	UFUNCTION()
	void OnVsyncCheckboxChanged(bool bIsChecked);

	UFUNCTION()
	void OnDynamicResolutionCheckboxChanged(bool bIsChecked);

	UFUNCTION()
	void ResolutionTextBlockHoveredDelegate() { SetTextBlockHovered(ResolutionTextBlock); }

	UFUNCTION()
	void ResolutionTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(ResolutionTextBlock); }

	UFUNCTION()
	void RefreshRateTextBlockHoveredDelegate() { SetTextBlockHovered(RefreshRateTextBlock); }

	UFUNCTION()
	void RefreshRateTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(RefreshRateTextBlock); }

	UFUNCTION()
	void BackTextBlockHoveredDelegate() { SetTextBlockHovered(BackTextBlock); }

	UFUNCTION()
	void BackTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(BackTextBlock); }

	UFUNCTION()
	void ResetToDefaultsTextBlockHoveredDelegate() { SetTextBlockHovered(ResetToDefaultsTextBlock); }

	UFUNCTION()
	void ResetToDefaultsTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(ResetToDefaultsTextBlock); }
};
