// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "NakatomiCharacter.h"
#include "Weapon.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Blueprint/UserWidget.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "InteractableComponent.h"
#include "Throwable.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

DECLARE_DELEGATE(FOnEnemyHitDelegate)

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
	UInputAction* ThrowWeaponAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* ThrowExplosiveAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MappingPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* WeaponSwitchingAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* AimDownSightsAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlayerHUD;

	FOnEnemyHitDelegate OnEnemyHit;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SprintSpeedMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ADSSpeedMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ADSAimSensitivityMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CameraBlendTime = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DefaultAimSensitivity = 45.0f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraADSSpringArmComponent = nullptr;
	
	float DefaultMovementSpeed;

	FTimerHandle FireTimerHandle;

	FTimerHandle CooldownTimerHandle;

	bool IsFiring = false;

	class UUserWidget* currentPlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* PerceptionSource;

	bool IsSpriting = false;

	bool IsADS = false;

	float AimSensitivity;

	float WeaponSpreadMultiplier = 1.0;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* HitMarkerSound;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Destroyed() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovementCallback(const FInputActionInstance& Instance);

	void LookCallback(const FInputActionInstance& Instance);

	void JumpCallback(const FInputActionInstance& Instance);

	void BeginFireCallback(const FInputActionInstance& Instance);

	void EndFireCallback(const FInputActionInstance& Instance);

	void QuitCallback(const FInputActionInstance& Instance);

	void SetSprintingCallback(const FInputActionInstance& Instance);

	void SetWalkingCallback(const FInputActionInstance& Instance);

	void WeaponSwitchingCallback(const FInputActionInstance& Instance);

	void BeginAimDownSightsCallback(const FInputActionInstance& Instance);

	void EndAimDownSightsCallback(const FInputActionInstance& Instance);

	virtual void OnFire() override;

	void WeaponCooldownHandler();

	void ClearAllTimers();

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmoCount();

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthCount();

	UFUNCTION(BlueprintCallable)
	int GetWeaponProjectiles();

	UFUNCTION(BlueprintCallable)
	float GetWeaponCooldown();

	UFUNCTION(BlueprintCallable)
	float GetWeaponSpread();

	void ThrowWeaponCallback();

	void ThrowExplosiveCallback();
	
	AThrowable* ThrowThrowable();

protected:
	virtual void CalculateHits(TArray<FHitResult>* hits) override;

	virtual void ProcessHits(TArray<FHitResult> hits) override;
	
	virtual void OnDamaged() override;
	
	virtual void OnDeath() override;

	void SetMovementSpeed();
};
