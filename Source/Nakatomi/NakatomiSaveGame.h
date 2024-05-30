// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GameFramework/SaveGame.h"
#include "NakatomiSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName = "Player Name";

	UPROPERTY(VisibleAnywhere, Category = Level)
	FString LevelName = "Level1";

	UPROPERTY(VisibleAnywhere, Category = Player)
	float PlayerHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Player)
	TArray<AWeapon*> WeaponInventory;

	UPROPERTY(VisibleAnywhere, Category = Player)
	TArray<TSubclassOf<AThrowable>> ThrowableInventory;

	UPROPERTY(VisibleAnywhere, Category = Player)
	int CurrentInventorySlot = 0;
	
	UFUNCTION(BlueprintCallable)
	void ResetPlayerValuesToDefault()
	{
		PlayerHealth = 100.0f;
	}
};
