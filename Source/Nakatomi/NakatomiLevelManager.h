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
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> NextLevel;

	int LevelKeys = 0;

	int CollectedLevelKeys = 0;
	
public:
	UFUNCTION()
	void LoadNextLevel();

	UFUNCTION()
	void IncrementInitialLevelKeys();

	UFUNCTION()
	void IncrementCollectedLevelKeys();
	
private:

	UFUNCTION()
	void BeginPlay(UWorld* world);
};
