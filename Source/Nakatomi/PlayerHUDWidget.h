// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "PlayerCharacter.h"
#include "PlayerHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class NAKATOMI_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ExpandCrosshair();

	UFUNCTION()
	void ShowHitMarker();

	UFUNCTION(BlueprintCallable)
	FString GetHealthbarText(APlayerCharacter* PlayerCharacter);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HealthText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AmmoStaticText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ProjectilesText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CooldownText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SpreadText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CrosshairImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* HitmarkerImage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* CrosshairFired;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* RevealHitmarker;
};
