// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsUIWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/NakatomiInteractiveWidget.h"
#include "MainMenuUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UMainMenuUIWidget : public UNakatomiInteractiveWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NewGameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LoadGameTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* OptionsTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* QuitTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> NewGameMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> LoadGameMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> OptionsMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NewGameLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ButtonHoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonHoveredTextColor = {0, 1, 0, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonUnhoveredTextColor = {1, 1, 1, 1};

private:
	UUserWidget* currentNewGameWidget;

	UUserWidget* currentLoadGameWidget;

	UOptionsUIWidget* currentOptionsMenuWidget;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void NewGameButtonOnClicked();

	UFUNCTION()
	void LoadGameButtonOnClicked();

	UFUNCTION()
	void OptionsButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();

	UFUNCTION()
	void PlayHoveredSound();
	
	UFUNCTION()
	void SetTextBlockHovered(UTextBlock* TextBlock);

	UFUNCTION()
	void SetTextBlockUnhovered(UTextBlock* TextBlock);

	UFUNCTION()
	void NewGameTextBlockHoveredDelegate() { SetTextBlockHovered(NewGameTextBlock); }

	UFUNCTION()
	void NewGameTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(NewGameTextBlock); }
	
	UFUNCTION()
	void LoadGameTextBlockHoveredDelegate() { SetTextBlockHovered(LoadGameTextBlock); }

	UFUNCTION()
	void LoadGameTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(LoadGameTextBlock); }
	
	UFUNCTION()
	void OptionsTextBlockHoveredDelegate() { SetTextBlockHovered(OptionsTextBlock); }

	UFUNCTION()
	void OptionsTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(OptionsTextBlock); }
	
	UFUNCTION()
	void QuitTextBlockHoveredDelegate() { SetTextBlockHovered(QuitTextBlock); }

	UFUNCTION()
	void QuitTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(QuitTextBlock); }
};
