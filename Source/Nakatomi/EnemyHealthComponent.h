// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "EnemyHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UEnemyHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser) override;
	
};
