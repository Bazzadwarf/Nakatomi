// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NakatomiInteractiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiInteractiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ButtonHoveredSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonHoveredTextColor = {0, 1, 0, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonUnhoveredTextColor = {1, 1, 1, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ButtonUnhoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ButtonClickedSound;

protected:
	UUserWidget* PreviousScreen;

public:

	UFUNCTION()
	void SetReturnScreen(UUserWidget* userWidget);

protected:
	UFUNCTION()
	void PlayHoveredSound();

	UFUNCTION()
	void SetTextBlockHovered(UTextBlock* TextBlock);

	UFUNCTION()
	void SetTextBlockUnhovered(UTextBlock* TextBlock);

	UFUNCTION()
	void PlayUnhoveredSound();

	UFUNCTION()
	void PlayClickedSound();

	UFUNCTION()
	void ReturnToPreviousScreen();
};
