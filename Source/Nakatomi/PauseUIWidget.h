// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsUIWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> OptionsMenuWidget;

private:
	UOptionsUIWidget* currentOptionsMenuWidget;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResumeButtonOnClicked();

	UFUNCTION()
	void OptionsButtonOnClicked();

	UFUNCTION()
	void SaveButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();

	UFUNCTION()
	void ExitGameButtonOnClicked();
};
