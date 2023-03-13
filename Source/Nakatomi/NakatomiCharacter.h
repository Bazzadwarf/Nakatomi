// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "Weapon.h"
#include "NakatomiCharacter.generated.h"

/**
 *
 */
UCLASS()
class NAKATOMI_API ANakatomiCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<class AWeapon>> DefaultWeaponInventory;

	UPROPERTY()
	TArray<AWeapon*> WeaponInventory;

	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;

private:

	UPROPERTY(VisibleDefaultsOnly)
	UHealthComponent* HealthComponent = nullptr;

	int CurrentInventorySlot = 0;

public:
	// Sets default values for this character's properties
	ANakatomiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UHealthComponent* GetHealthComponent();

	void SetHealthComponent(UHealthComponent* healthComponent);

	void SetInventoryToDefault();

	void SelectInventorySlot(int slot);

	void InventoryIncrement();

	void InventoryDecrement();

	void AddWeaponToInventory(TSubclassOf<class AWeapon> weapon);

	void AddWeaponToInventory(AWeapon* weapon);

	void RemoveWeaponFromInventory(int i);

	void RemoveWeaponFromInventory(AWeapon* weapon);

	void RemoveCurrentWeaponFromInventory();

	AWeapon* InitializeWeapon(TSubclassOf<class AWeapon> weapon);

	AWeapon* GetCurrentWeapon();

	void SetCurrentWeapon(AWeapon* weapon);

	int GetCurrentInventorySlot();

	virtual void OnFire();

protected:

	virtual void CalculateHits(TArray<FHitResult>* hits);

	virtual void ProcessHits(TArray<FHitResult> hits);
};
