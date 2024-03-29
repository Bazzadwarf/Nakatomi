// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiGameInstance.h"

UNakatomiAIAttackTokenManager* UNakatomiGameInstance::GetAIAttackTokenManager()
{
	return IsValid(AIAttackTokenManager) ? AIAttackTokenManager : (AIAttackTokenManager = NewObject<UNakatomiAIAttackTokenManager>(this, TEXT("AI Attack Token Manager")));
}

UNakatomiLevelManager* UNakatomiGameInstance::GetCurrentLevelManager()
{
	return IsValid(currentLevelManager)
		       ? currentLevelManager
		       : currentLevelManager = NewObject<UNakatomiLevelManager>(this, TEXT("Level Manager"));
}

void UNakatomiGameInstance::SetCurrentLevelManager(UNakatomiLevelManager* NewLevelManager)
{
	currentLevelManager = NewLevelManager;
}
