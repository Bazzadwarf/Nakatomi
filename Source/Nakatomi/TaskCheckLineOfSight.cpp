// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskCheckLineOfSight.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "NakatomiCharacter.h"
#include "PlayerCharacter.h"

EBTNodeResult::Type UTaskCheckLineOfSight::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto BlackboardComponent = owner.GetBlackboardComponent();

	if (!BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}

	auto selfActor = Cast<ANakatomiCharacter>(
		BlackboardComponent->GetValueAsObject(SelfActorKey.SelectedKeyName));

	if (!selfActor)
	{
		return EBTNodeResult::Failed;
	}

	AWeapon* CurrentWeapon = selfActor->GetCurrentWeapon();

	if (!CurrentWeapon)
	{
		return EBTNodeResult::Failed;
	}

	// Calculate starting position and direction
	FVector TraceStart = selfActor->GetTransform().GetLocation();
	FRotator PlayerRot = selfActor->GetTransform().GetRotation().Rotator();
	TraceStart = selfActor->GetRootComponent()->GetComponentLocation();
	FVector AimDir = PlayerRot.Vector();
	AimDir.Z = 0.0;

	TraceStart = TraceStart + AimDir * ((selfActor->GetInstigator()->GetActorLocation() - TraceStart) | AimDir);

	// Calculate the hit results from the trace
	TArray<FHitResult> HitResults;

	// Set up the collision query params, use the Weapon trace settings, Ignore the actor firing this trace
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, selfActor->GetInstigator());
	TraceParams.bReturnPhysicalMaterial = true;

	FVector MaxHitLoc = TraceStart + (AimDir * CurrentWeapon->GetWeaponProperties()->ProjectileRange);

	GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, MaxHitLoc, ECC_GameTraceChannel1, TraceParams);

	for (FHitResult Result : HitResults)
	{
		if (Cast<APlayerCharacter>(Result.GetActor()))
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
