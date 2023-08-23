// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskGetLocationNearLocation.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include <NavigationSystem.h>

EBTNodeResult::Type UTaskGetLocationNearLocation::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	auto enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	auto blackboardComponent = owner.GetBlackboardComponent();
	auto navigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FVector sourceLocation = blackboardComponent->GetValueAsVector(SourceLocationKey.SelectedKeyName);

	if (blackboardComponent && navigationSystem && sourceLocation != FVector::ZeroVector)
	{
		FNavLocation navLocation;
		navigationSystem->GetRandomReachablePointInRadius(sourceLocation, MaximumDistance, navLocation);

		blackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, navLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
