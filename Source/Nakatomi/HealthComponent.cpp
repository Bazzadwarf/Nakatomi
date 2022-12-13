// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::TakeDamage()
{
}

void UHealthComponent::DecrementHealth(float value)
{
	value *= !CanDamage;

	CurrentHealth -= value;

	if (CurrentHealth <= 0.0f)
	{
		// TODO: Call some death logic here
		OnDeath.ExecuteIfBound();
	}
}

void UHealthComponent::IncrementHealth(float value)
{
	CurrentHealth += value;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float value)
{
	MaxHealth = value;
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UHealthComponent::SetCurrentHealth(float value)
{
	// TODO: We might want to add some extra checking here
	CurrentHealth = value;
}

void UHealthComponent::ResetHealth()
{
	CurrentHealth = MaxHealth;
}

void UHealthComponent::RecoverHealth(float value)
{
	// TODO: We might want to add some extra checking here
	IncrementHealth(value);
}

bool UHealthComponent::GetIsDead()
{
	return IsDead;
}

void UHealthComponent::SetIsDead(bool isDead)
{
	IsDead = isDead;
}

bool UHealthComponent::GetCanDamage()
{
	return CanDamage;
}

void UHealthComponent::SetCanDamage(bool canDamage)
{
	CanDamage = canDamage;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




