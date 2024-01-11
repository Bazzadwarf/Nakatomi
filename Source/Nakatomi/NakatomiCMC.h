// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nakatomi.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NakatomiCMC.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMove
{
	CMOVE_None	UMETA(Hidden),
	CMOVE_Slide UMETA(DisplayName = "Slide"),
	CMOVE_MAX	UMETA(Hidden),
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
		typedef FSavedMove_Character Super;

		// Flag
		uint8 Saved_bWantsToSprint:1;

		uint8 Saved_bPrevWantsToCrouch:1;
		
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	class FNetworkPredictionData_Client_Nakatomi : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_Nakatomi(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

	UPROPERTY(EditDefaultsOnly)
	float Sprint_MaxWalkSpeed;

	UPROPERTY(EditDefaultsOnly)
	float Walk_MaxWalkSpeed;

	UPROPERTY(EditDefaultsOnly)
	float Slide_MinSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_EnterImpulse = 2000.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_GravityForce = 5000.f;

	UPROPERTY(EditDefaultsOnly)
	float Slide_Friction = 1.3f;
	
	bool Safe_bWantsToSprint;
	bool Safe_bPrevWantsToCrouch;

	UPROPERTY(Transient)
	ANakatomiCharacter* NakatomiCharacterOwner;
	
public:
	UNakatomiCMC();

protected:
	void InitializeComponent() override;

	FNetworkPredictionData_Client* GetPredictionData_Client() const override;
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

	UFUNCTION()
	bool IsCustomMovementMode(ECustomMovementMove InCustomMovementMode) const;

private:

	void EnterSlide();

	void ExitSlide();

	void PhysSlide(float deltaTime, int32 Iterations); // Every movement mode requires a physics function to work

	bool GetSlideSurface(FHitResult& Hit) const;
};
