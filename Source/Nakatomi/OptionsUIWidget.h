// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBox.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "OptionsUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UOptionsUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBox* ResolutionSelector;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* FullscreenBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ApplyButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetToDefaultsButton;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ApplyButtonOnClicked();

	UFUNCTION()
	void BackButtonOnClicked();

	
	UFUNCTION()
	void ResetToDefaultsButtonOnClicked();
};
