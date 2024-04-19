// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiLevelManager.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiLevelManager : public UObject
{
	GENERATED_BODY()

	UNakatomiLevelManager();

private:

	int InitialLevelKeys = 0;

	int CollectedLevelKeys = 0;
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel(TSoftObjectPtr<UWorld> NextLevel);

	UFUNCTION(BlueprintCallable)
	void IncrementInitialLevelKeys();

	UFUNCTION(BlueprintCallable)
	void IncrementCollectedLevelKeys();

	UFUNCTION(BlueprintCallable)
	int GetInitialLevelKeysCount();

	UFUNCTION(BlueprintCallable)
	int GetCollectedLevelKeysCount();
	
private:

	UFUNCTION()
	void BeginPlay(UWorld* world);
};
