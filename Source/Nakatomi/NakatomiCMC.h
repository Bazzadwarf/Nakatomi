// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nakatomi.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NakatomiCMC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDashStartDelegate);

UENUM(BlueprintType)
enum ECustomMovementMove
{
	CMOVE_None UMETA(Hidden),
	CMOVE_Slide UMETA(DisplayName = "Slide"),
	CMOVE_Dash UMETA(DisplayName = "Dash"),
	CMOVE_MAX UMETA(Hidden),
};

/**
 * 
 */
UCLASS()
class NAKATOMI_API UNakatomiCMC : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_Nakatomi : public FSavedMove_Character
	{
		using Super = FSavedMove_Character;

	public:
		enum CompressedFlags
		{
			FLAG_Sprint = 0x10,
			FLAG_Dash = 0x20,
			FLAG_Custom2 = 0x30,
			FLAG_Custom3 = 0x40,
		};

		// Flag
		uint8 Saved_bWantsToSprint : 1;
		uint8 Saved_bWantsToSlide : 1;
		uint8 Saved_bWantsToAds : 1;
		uint8 Saved_bWantsToDash : 1;

		virtual bool
		CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, const FVector& NewAccel,
		                        FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	class FNetworkPredictionData_Client_Nakatomi : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_Nakatomi(const UCharacterMovementComponent& ClientMovement);

		using Super = FNetworkPredictionData_Client_Character;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

	UPROPERTY(EditDefaultsOnly)
	float Sprint_MaxWalkSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
	float Walk_MaxWalkSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly)
	float Crouch_MaxWalkSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_MinSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_EnterImpulse = 2000.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_GravityForce = 2500.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_Friction = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float Ads_Multiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float Dash_Impulse = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	float Dash_CooldownDuration = 1.0f;

	bool Safe_bWantsToSprint;
	bool Safe_bWantsToSlide;
	bool Safe_bWantsToAds;
	bool Safe_bWantsToDash;

	float DashStartTime;
	FTimerHandle TimerHandle_DashCooldown;

	UPROPERTY(Transient)
	ANakatomiCharacter* NakatomiCharacterOwner;

public:
	UPROPERTY(BlueprintAssignable)
	FDashStartDelegate DashStartDelegate;

public:
	UNakatomiCMC();

protected:
	virtual void InitializeComponent() override;

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	virtual bool IsMovingOnGround() const override;

	virtual bool CanCrouchInCurrentState() const override;

	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

public:
	UFUNCTION(BlueprintCallable)
	void EnableSprint();

	UFUNCTION(BlueprintCallable)
	void DisableSprint();

	UFUNCTION(BlueprintCallable)
	void EnableCrouch();

	UFUNCTION(BlueprintCallable)
	void DisableCrouch();

	UFUNCTION(BlueprintCallable)
	void EnableSlide();

	UFUNCTION(BlueprintCallable)
	void DisableSlide();

	UFUNCTION(BlueprintCallable)
	void EnableAds();

	UFUNCTION(BlueprintCallable)
	void DisableAds();

	UFUNCTION(BlueprintCallable)
	void EnableDash();

	UFUNCTION(BlueprintCallable)
	void DisableDash();

	UFUNCTION()
	bool IsCustomMovementMode(ECustomMovementMove InCustomMovementMode) const;

private:
	void EnterSlide();
	void ExitSlide();
	void PhysSlide(float deltaTime, int32 Iterations); // Every movement mode requires a physics function to work
	bool GetSlideSurface(FHitResult& Hit) const;

	void OnDashCooldownFinished();
	bool CanDash();
	void PerformDash();
};
