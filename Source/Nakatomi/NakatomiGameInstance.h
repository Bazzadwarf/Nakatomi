// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NakatomiAIAttackTokenManager.h"
#include "NakatomiLevelManager.h"
#include "NakatomiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UNakatomiLevelManager* currentLevelManager;

private:

	UPROPERTY()
	UNakatomiAIAttackTokenManager* AIAttackTokenManager;

public:

	UFUNCTION(BlueprintCallable)
	UNakatomiAIAttackTokenManager* GetAIAttackTokenManager();

	UFUNCTION(BlueprintCallable)
	UNakatomiLevelManager* GetCurrentLevelManager();

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelManager(UNakatomiLevelManager* NewLevelManager);
};
