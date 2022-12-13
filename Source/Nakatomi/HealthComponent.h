// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE(FOnDeathDelegate)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKATOMI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	FOnDeathDelegate OnDeath;

private:

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	bool IsDead = false;

	bool CanDamage;

public:

	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	void TakeDamage();
	
	UFUNCTION()
	void DecrementHealth(float value);

	UFUNCTION()
	void IncrementHealth(float value);

	UFUNCTION()
	float GetMaxHealth();

	UFUNCTION()
	void SetMaxHealth(float value);

	UFUNCTION()
	float GetCurrentHealth();

	UFUNCTION()
	void SetCurrentHealth(float value);

	UFUNCTION()
	void ResetHealth();

	UFUNCTION()
	void RecoverHealth(float healing);

	UFUNCTION()
	bool GetIsDead();

	UFUNCTION()
	void SetIsDead(bool isDead);

	UFUNCTION()
	bool GetCanDamage();

	UFUNCTION()
	void SetCanDamage(bool canDamage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
