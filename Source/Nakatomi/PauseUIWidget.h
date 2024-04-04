// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsUIWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/NakatomiInteractiveWidget.h"
#include "PauseUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UPauseUIWidget : public UNakatomiInteractiveWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResumeTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* OptionsTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SaveButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SaveTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* QuitTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExitGameTextBlock;
	
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

	UFUNCTION()
	void ResumeTextBlockHoveredDelegate() { SetTextBlockHovered(ResumeTextBlock); }

	UFUNCTION()
	void ResumeTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(ResumeTextBlock); }

	UFUNCTION()
	void OptionsTextBlockHoveredDelegate() { SetTextBlockHovered(OptionsTextBlock); }

	UFUNCTION()
	void OptionsTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(OptionsTextBlock); }

	UFUNCTION()
	void SaveTextBlockHoveredDelegate() { SetTextBlockHovered(SaveTextBlock); }

	UFUNCTION()
	void SaveTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(SaveTextBlock); }

	UFUNCTION()
	void QuitTextBlockHoveredDelegate() { SetTextBlockHovered(QuitTextBlock); }

	UFUNCTION()
	void QuitTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(QuitTextBlock); }

	UFUNCTION()
	void ExitGameTextBlockHoveredDelegate() { SetTextBlockHovered(ExitGameTextBlock); }

	UFUNCTION()
	void ExitGameTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(ExitGameTextBlock); }
};
