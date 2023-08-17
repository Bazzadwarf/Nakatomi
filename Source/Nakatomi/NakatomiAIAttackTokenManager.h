// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NakatomiAIAttackTokenManager.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiAIAttackTokenManager : public UObject
{
	GENERATED_BODY()
	
private:
	
	// TODO: This should really be set by the current difficulty setting.
	static const int MAX_ATTACK_TOKEN = 5;

	int attackTokensUsed = 0;

public:

	bool RequestToken();

	void ReleaseToken();

	void Reset();

};
