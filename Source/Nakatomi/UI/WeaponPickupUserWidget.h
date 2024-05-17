// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "WeaponPickupUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UWeaponPickupUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ProjectilesText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CooldownText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SpreadText;

};
