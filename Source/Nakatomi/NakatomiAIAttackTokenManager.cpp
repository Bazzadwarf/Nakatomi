// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiAIAttackTokenManager.h"

bool UNakatomiAIAttackTokenManager::RequestToken()
{
	if (attackTokensUsed == MAX_ATTACK_TOKEN)
	{
		return false;
	}
	attackTokensUsed++;

	return true;
}

bool UNakatomiAIAttackTokenManager::ReleaseToken()
{
	if (attackTokensUsed > 0)
	{
		attackTokensUsed--;
	}	

	return false;
}

void UNakatomiAIAttackTokenManager::Reset()
{
	attackTokensUsed = 0;
}
