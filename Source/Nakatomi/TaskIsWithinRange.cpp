// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskIsWithinRange.h"
#include "EnemyAIController.h"
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>

EBTNodeResult::Type UTaskIsWithinRange::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto BlackboardComponent = owner.GetBlackboardComponent();

	if (!BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}

	auto NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FVector SourceLocation = BlackboardComponent->GetValueAsVector(SourceLocationKey.SelectedKeyName);
	ANakatomiCharacter* selfActor = Cast<ANakatomiCharacter>(
		BlackboardComponent->GetValueAsObject(SelfActorKey.SelectedKeyName));

	if (NavigationSystem && SourceLocation != FVector::ZeroVector)
	{
		double Distance = -1.0;
		FNavLocation NavLocation;

		NavigationSystem->GetPathLength(SourceLocation, selfActor->GetTransform().GetLocation(), Distance);

		return Distance <= MaximumDistance ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
