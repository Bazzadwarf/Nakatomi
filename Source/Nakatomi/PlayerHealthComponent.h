// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "PlayerHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UPlayerHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
