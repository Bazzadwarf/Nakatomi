// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NakatomiAIAttackTokenManager.h"
#include "NakatomiLevelManager.h"
#include "NakatomiSaveFileInfo.h"
#include "NakatomiSaveGame.h"
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

	UPROPERTY()
	UNakatomiSaveGame* SaveGameObject = nullptr;

public:

	UFUNCTION(BlueprintCallable)
	UNakatomiAIAttackTokenManager* GetAIAttackTokenManager();

	UFUNCTION(BlueprintCallable)
	UNakatomiLevelManager* GetCurrentLevelManager();

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelManager(UNakatomiLevelManager* NewLevelManager);

	UFUNCTION(BlueprintCallable)
	UNakatomiSaveGame* LoadGameFromSlot(FString SaveSlotName);

	UFUNCTION(BlueprintCallable)
	bool SaveGame(bool ResetDefaults = false);

	UFUNCTION(BlueprintCallable)
	UNakatomiSaveGame* GetSaveGameObject();

	UFUNCTION(BlueprintCallable)
	UNakatomiSaveGame* CreateNewSaveGame(FString PlayerName);

	UFUNCTION(BlueprintCallable)
	TArray<FNakatomiSaveFileInfo> GetAllSaveFilesFromDisk();
};
