// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiInteractiveWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "LoadGameUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API ULoadGameUserWidget : public UNakatomiInteractiveWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CancelButtonTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* SavedGamesScrollBox;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void CancelButtonOnClicked();

	UFUNCTION()
	void CancelButtonHoveredDelegate() { SetTextBlockHovered(CancelButtonTextBlock); }
	
	UFUNCTION()
	void CancelButtonUnhoveredDelegate() { SetTextBlockUnhovered(CancelButtonTextBlock); }
};
