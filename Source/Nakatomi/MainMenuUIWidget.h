// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsUIWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UMainMenuUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

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
};
