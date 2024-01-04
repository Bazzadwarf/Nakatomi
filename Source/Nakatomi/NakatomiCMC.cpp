// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiCMC.h"

#include <GameFramework/Character.h>

UNakatomiCMC::UNakatomiCMC(): Safe_bWantsToSprint(false)
{
	NavAgentProps.bCanCrouch = true;
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
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

// Reset a save move object to empty
void UNakatomiCMC::FSavedMove_Nakatomi::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}

uint8 UNakatomiCMC::FSavedMove_Nakatomi::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result = ~FLAG_Custom_0;
	
	return Result;
}

void UNakatomiCMC::FSavedMove_Nakatomi::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	UNakatomiCMC* CharacterMovement = Cast<UNakatomiCMC>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

void UNakatomiCMC::FSavedMove_Nakatomi::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);

	UNakatomiCMC* CharacterMovement = Cast<UNakatomiCMC>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
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
