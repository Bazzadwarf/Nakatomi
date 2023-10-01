// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "PauseUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UPauseUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseApplicationButton;

public:
	virtual void NativeConstruct() override;

private:
	void ResumeButtonOnClicked();

	void OptionsButtonOnClicked();

	void SaveButtonOnClicked();

	void QuitButtonOnClicked();

	void CloseApplicationButtonOnClicked();
};
