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

protected:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANakatomiFieldSystemActor> FieldSystemActor;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionParticleSystem;

	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxDamage = 150.f;

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Explode();
};
