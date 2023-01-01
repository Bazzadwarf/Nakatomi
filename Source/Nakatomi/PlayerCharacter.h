// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "NakatomiCharacter.h"
#include "Weapon.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
//class UEnhancedInputComponent;

/**
 * 
 */
UCLASS()
class NAKATOMI_API APlayerCharacter : public ANakatomiCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* QuitAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int MappingPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<TSubclassOf<class AWeapon>> DefaultWeaponInventory;

	UPROPERTY()
		TArray<AWeapon*> WeaponInventory;

	// TODO: Add weapon switching actions

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float SprintSpeedMultiplier = 2.0f;

private:

	UPROPERTY()
		USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY()
		UCameraComponent* CameraComponent = nullptr;

	float DefaultMovementSpeed;

	int CurrentInventorySlot = 0;

	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovementCallback(const FInputActionInstance& Instance);

	void LookCallback(const FInputActionInstance& Instance);

	void JumpCallback(const FInputActionInstance& Instance);

	void FireCallback(const FInputActionInstance& Instance);

	void QuitCallback(const FInputActionInstance& Instance);

	void SetSprintingCallback(const FInputActionInstance& Instance);

	void SetWalkingCallback(const FInputActionInstance& Instance);

	void CalculateHits(TArray<FHitResult>* hits);

	void SetInventoryToDefault();

	void SelectInventorySlot(int slot);

	void InventoryIncrementCallback(const FInputActionInstance& Instance);

	void InventoryDecrementCallback(const FInputActionInstance& Instance);

	AWeapon* InitializeWeapon(TSubclassOf<class AWeapon> weapon);

	AWeapon* GetCurrentWeapon();

	void SetCurrentWeapon(AWeapon* weapon);
};
