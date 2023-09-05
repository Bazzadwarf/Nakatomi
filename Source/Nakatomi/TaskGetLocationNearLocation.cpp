// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGetLocationNearLocation.h"
#include "EnemyAIController.h"
#include <NavigationSystem.h>

EBTNodeResult::Type UTaskGetLocationNearLocation::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto BlackboardComponent = owner.GetBlackboardComponent();

	if (!BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}
	
	auto NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FVector SourceLocation = BlackboardComponent->GetValueAsVector(SourceLocationKey.SelectedKeyName);

	if (BlackboardComponent && NavigationSystem && SourceLocation != FVector::ZeroVector)
	{
		double Distance = -1.0;
		FNavLocation NavLocation;

		while (Distance < MinimumDistance)
		{
			NavigationSystem->GetRandomReachablePointInRadius(SourceLocation, MaximumDistance, NavLocation);
			NavigationSystem->GetPathLength(SourceLocation, NavLocation.Location, Distance);
		}

		BlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
