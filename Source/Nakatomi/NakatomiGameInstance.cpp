// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiGameInstance.h"

UNakatomiAIAttackTokenManager* UNakatomiGameInstance::GetAIAttackTokenManager()
{
	return IsValid(AIAttackTokenManager) ? AIAttackTokenManager : (AIAttackTokenManager = NewObject<UNakatomiAIAttackTokenManager>(this, TEXT("AI Attack Token Manager")));
}

UNakatomiLevelManager* UNakatomiGameInstance::GetCurrentLevelManager()
{
	if (IsValid(currentLevelManager))
	{
		return currentLevelManager;
	}

	UE_LOG(LogTemp, Warning, TEXT("No Level manager set."))

	return nullptr;
}

void UNakatomiGameInstance::SetCurrentLevelManager(UNakatomiLevelManager* NewLevelManager)
{
	currentLevelManager = NewLevelManager;
}
