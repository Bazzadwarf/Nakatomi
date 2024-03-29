// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiCMC.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>
#include "NakatomiCharacter.h"

UNakatomiCMC::UNakatomiCMC(): Safe_bWantsToSprint(false)
{
	NavAgentProps.bCanCrouch = true;
}

void UNakatomiCMC::InitializeComponent()
{
	Super::InitializeComponent();

	NakatomiCharacterOwner = Cast<ANakatomiCharacter>(GetOwner());
}

void UNakatomiCMC::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaxWalkSpeed = Walk_MaxWalkSpeed;
}

// Checks if we can combine the NewMove with the current move to save on data.
// If all the data in a saved move is identical, if true, we cam tell the server to run the existing move instead.
bool UNakatomiCMC::FSavedMove_Nakatomi::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter,
	float MaxDelta) const
{
	FSavedMove_Nakatomi* newMove = static_cast<FSavedMove_Nakatomi*>(NewMove.Get());

	// Check if values can be combined, if not return false, if true allow super to handle combining data
	if (Saved_bWantsToSprint != newMove->Saved_bWantsToSprint)
	{
		return false;
	}

	if (Saved_bWantsToDash != newMove->Saved_bWantsToDash)
	{
		return false;
	}
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

// Reset a save move object to empty
void UNakatomiCMC::FSavedMove_Nakatomi::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
	Saved_bWantsToSlide = 0;
	Saved_bWantsToAds = 0;
	Saved_bWantsToDash = 0;
}

uint8 UNakatomiCMC::FSavedMove_Nakatomi::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result = ~FLAG_Custom_0;
	if (Saved_bWantsToDash) Result = ~FLAG_Dash;
	
	return Result;
}

void UNakatomiCMC::FSavedMove_Nakatomi::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	UNakatomiCMC* CharacterMovement = Cast<UNakatomiCMC>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
	Saved_bWantsToSlide = CharacterMovement->Safe_bWantsToSlide;
	Saved_bWantsToAds = CharacterMovement->Safe_bWantsToAds;
	Saved_bWantsToDash = CharacterMovement->Safe_bWantsToDash;
}

void UNakatomiCMC::FSavedMove_Nakatomi::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);

	UNakatomiCMC* CharacterMovement = Cast<UNakatomiCMC>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
	CharacterMovement->Safe_bWantsToSlide = Saved_bWantsToSlide;
	CharacterMovement->Safe_bWantsToAds = Saved_bWantsToAds;
	CharacterMovement->Safe_bWantsToDash = Saved_bWantsToDash;
}

UNakatomiCMC::FNetworkPredictionData_Client_Nakatomi::FNetworkPredictionData_Client_Nakatomi(
	const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
}

FSavedMovePtr UNakatomiCMC::FNetworkPredictionData_Client_Nakatomi::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Nakatomi());
}

FNetworkPredictionData_Client* UNakatomiCMC::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		UNakatomiCMC* MutableThis = const_cast<UNakatomiCMC*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Nakatomi(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UNakatomiCMC::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	Safe_bWantsToDash = (Flags & FSavedMove_Nakatomi::FLAG_Dash) != 0;
}

void UNakatomiCMC::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Walking)
	{
		if (Safe_bWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		}
		else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}

		if (Safe_bWantsToAds)
		{
			MaxWalkSpeed *= Ads_Multiplier;
		}
	}

	if (bWantsToCrouch)
	{
		if (Safe_bWantsToAds)
		{
			MaxWalkSpeedCrouched = Crouch_MaxWalkSpeed * Ads_Multiplier;
		}
		else
		{
			MaxWalkSpeedCrouched = Crouch_MaxWalkSpeed;
		}
	}
}

bool UNakatomiCMC::IsMovingOnGround() const
{
	return Super::IsMovingOnGround() || IsCustomMovementMode(CMOVE_Slide);
}

bool UNakatomiCMC::CanCrouchInCurrentState() const
{
	return Super::CanCrouchInCurrentState() && IsMovingOnGround();
}

void UNakatomiCMC::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	// Slide
	if (MovementMode == MOVE_Walking && Safe_bWantsToSlide && !Safe_bWantsToAds)
	{
		FHitResult PotentialSlideSurface;
		if (Velocity.SizeSquared() > pow(Slide_MinSpeed, 2) && GetSlideSurface(PotentialSlideSurface))
		{
			EnterSlide();
		}
	}

	if (IsCustomMovementMode(CMOVE_Slide) && !Safe_bWantsToSlide)
	{
		ExitSlide();
	}

	// Dash
	if (Safe_bWantsToDash && CanDash() && !Safe_bWantsToAds)
	{
		PerformDash();
		Safe_bWantsToDash = false;
	}
	
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

void UNakatomiCMC::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch (CustomMovementMode)
	{
	case CMOVE_Slide:
		PhysSlide(deltaTime, Iterations);
		break;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
	}
}

void UNakatomiCMC::EnableSprint()
{
	Safe_bWantsToSprint = true;
}

void UNakatomiCMC::DisableSprint()
{
	Safe_bWantsToSprint = false;
}

void UNakatomiCMC::EnableCrouch()
{
	bWantsToCrouch = true;
}

void UNakatomiCMC::DisableCrouch()
{
	bWantsToCrouch = false;
}

void UNakatomiCMC::EnableSlide()
{
	Safe_bWantsToSlide = true;
}

void UNakatomiCMC::DisableSlide()
{
	Safe_bWantsToSlide = false;
}

void UNakatomiCMC::EnableAds()
{
	Safe_bWantsToAds = true;
}

void UNakatomiCMC::DisableAds()
{
	Safe_bWantsToAds = false;
}

void UNakatomiCMC::EnableDash()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - DashStartTime >= Dash_CooldownDuration)
	{
		Safe_bWantsToDash = true;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DashCooldown, this, &UNakatomiCMC::OnDashCooldownFinished,
		                                       Dash_CooldownDuration - (CurrentTime - DashStartTime));
	}	
}

void UNakatomiCMC::DisableDash()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_DashCooldown);
	Safe_bWantsToDash = false;
}

bool UNakatomiCMC::IsCustomMovementMode(ECustomMovementMove InCustomMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
}

void UNakatomiCMC::SetMaxWalkSpeed(float newMaxSpeed)
{
	Walk_MaxWalkSpeed = newMaxSpeed;
}

void UNakatomiCMC::SetMaxWalkSpeedToDefault()
{
	Walk_MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void UNakatomiCMC::EnterSlide()
{
	Safe_bWantsToSlide = true;
	Velocity += Velocity.GetSafeNormal2D() * Slide_EnterImpulse;
	SetMovementMode(MOVE_Custom, CMOVE_Slide);
}

void UNakatomiCMC::ExitSlide()
{
	Safe_bWantsToSlide = false;

	FQuat NewRotation = FRotationMatrix::MakeFromXZ(UpdatedComponent->GetForwardVector().GetSafeNormal2D(), FVector::UpVector).ToQuat();
	FHitResult Hit;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, true, Hit);
	SetMovementMode(MOVE_Walking);
}

void UNakatomiCMC::PhysSlide(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME) return;

	// This is probably not needed for Sliding but including for completeness, will likely remove later.
	RestorePreAdditiveRootMotionVelocity();

	FHitResult SurfaceHit;
	if (!GetSlideSurface(SurfaceHit) || Velocity.SizeSquared() < pow(Slide_MinSpeed, 2))
	{
		ExitSlide();
		StartNewPhysics(deltaTime, Iterations);
	}

	// Surface Gravity
	Velocity += Slide_GravityForce * FVector::DownVector * deltaTime;

	// Calculate Strafe
	if (FMath::Abs(FVector::DotProduct(Acceleration.GetSafeNormal(), UpdatedComponent->GetRightVector())) > 0.5f)
	{
		Acceleration = Acceleration.ProjectOnTo(UpdatedComponent->GetRightVector());
	}
	else
	{
		Acceleration = FVector::ZeroVector;
	}

	// Calculate Velocity
	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		CalcVelocity(deltaTime, Slide_Friction, true, GetMaxBrakingDeceleration());
	}
	ApplyRootMotionToVelocity(deltaTime);

	// Perform Move
	Iterations++;
	bJustTeleported = false;

	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	FQuat OldRotation = UpdatedComponent->GetComponentRotation().Quaternion();
	
	FHitResult Hit(1.f);
	FVector AdjustedVelocity = Velocity * deltaTime;
	FVector VelocityPlaneDirection = FVector::VectorPlaneProject(Velocity, SurfaceHit.Normal).GetSafeNormal();
	FQuat NewRotation = FRotationMatrix::MakeFromXZ(VelocityPlaneDirection, SurfaceHit.Normal).ToQuat();
	SafeMoveUpdatedComponent(AdjustedVelocity, NewRotation, true, Hit);

	// Post Move Checks
	if (Hit.Time < 1.f)
	{
		HandleImpact(Hit, deltaTime, AdjustedVelocity);
		SlideAlongSurface(AdjustedVelocity, (1.f - Hit.Time), Hit.Normal, Hit, true);
	}

	FHitResult NewSurfaceHit;
	if (!GetSlideSurface(NewSurfaceHit) || Velocity.SizeSquared() < pow(Slide_MinSpeed, 2))
	{
		ExitSlide();
	}

	// Update outgoing Velocity and Acceleration
	if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
	}
}

bool UNakatomiCMC::GetSlideSurface(FHitResult& Hit) const
{
	const FVector Start = UpdatedComponent->GetComponentLocation();
	const FVector End = Start + CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f * FVector::DownVector;
	const FName ProfileName = TEXT("BlockAll");
	
	return GetWorld()->LineTraceSingleByProfile(Hit, Start, End, ProfileName);
}

void UNakatomiCMC::OnDashCooldownFinished()
{
	Safe_bWantsToDash = true;
}

bool UNakatomiCMC::CanDash()
{
	return (IsWalking() || IsFalling()) && !IsCrouching() && !Safe_bWantsToAds;
}

void UNakatomiCMC::PerformDash()
{
	DashStartTime = GetWorld()->GetTimeSeconds();

	FVector DashDirection = (Acceleration.IsNearlyZero() ? UpdatedComponent->GetForwardVector() : Acceleration).GetSafeNormal2D();
	Velocity = Dash_Impulse * (DashDirection + FVector::UpVector * .1f);

	FQuat NewRotation = FRotationMatrix::MakeFromXZ(DashDirection, FVector::UpVector).ToQuat();
	FHitResult Hit;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, false, Hit);
	
	NakatomiCharacterOwner->PlayAnimMontage(Dash_Montage);

	SetMovementMode(MOVE_Falling);

	DashStartDelegate.Broadcast();
}
