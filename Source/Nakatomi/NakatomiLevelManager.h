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
	
public:

	UFUNCTION()
	void LoadNextLevel();

private:

	UFUNCTION()
	void BeginPlay(UWorld* world);
};
