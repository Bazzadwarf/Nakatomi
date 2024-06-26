// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiInteractiveWidget.h"
#include "Components/Button.h"
#include "Nakatomi/NakatomiSaveFileInfo.h"
#include "SaveGameEntryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API USaveGameEntryUserWidget : public UNakatomiInteractiveWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadSaveButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentLevelTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DateTimeSavedTextBlock;

private:
	FNakatomiSaveFileInfo SaveFileInfo;
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetSaveInfo(FNakatomiSaveFileInfo SaveFile);

private:
	UFUNCTION()
	void LoadSaveButtonOnClicked();

	UFUNCTION()
	void LoadSaveButtonHoveredDelegate();

	UFUNCTION()
	void LoadSaveButtonUnhoveredDelegate();
};
