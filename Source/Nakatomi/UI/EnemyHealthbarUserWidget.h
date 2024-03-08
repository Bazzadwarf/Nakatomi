// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Nakatomi/EnemyCharacter.h"
#include "EnemyHealthbarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UEnemyHealthbarUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Healthbar;

	AEnemyCharacter* Owner;

public:

	void BindOwner(AEnemyCharacter* NewOwner);

private:
	
	UFUNCTION()
	void UpdateHealthbar();
};
