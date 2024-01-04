// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "NakatomiCMC.h"
#include "Throwable.h"
#include "Weapon.h"
#include "NakatomiCharacter.generated.h"


DECLARE_DELEGATE(FOnFireDelegate)


/**
 *
 */
UCLASS()
class NAKATOMI_API ANakatomiCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	FOnFireDelegate OnFired;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<class AWeapon>> DefaultWeaponInventory;

	UPROPERTY()
	TArray<AWeapon*> WeaponInventory;

	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<AThrowable>> ThrowableInventory;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNakatomiCMC* NakatomiCMC;
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	UHealthComponent* HealthComponent = nullptr;

	int CurrentInventorySlot = 0;

	UPROPERTY(EditDefaultsOnly)
	int MaximumThrowableInventorySize = 4;

	
public:
	// Sets default values for this character's properties
	ANakatomiCharacter(const FObjectInitializer& ObjectInitializer);

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

	TSubclassOf<AThrowable> PopThrowableFromInventory();

	void PushThrowableToInventory(TSubclassOf<AThrowable> Throwable);

	UNakatomiCMC* GetCharacterMovementComponent();

protected:
	virtual void CalculateHits(TArray<FHitResult>* hits);

	virtual void ProcessHits(TArray<FHitResult> hits);

	UFUNCTION()
	virtual void OnDamaged();

	UFUNCTION()
	virtual void OnDeath();
};
