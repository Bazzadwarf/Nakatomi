// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "DemolitionCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API ADemolitionCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void Explode();

};
