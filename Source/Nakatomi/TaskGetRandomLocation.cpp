// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskGetRandomLocation.h"
#include "EnemyAIController.h"
#include "navigationSystem.h"

EBTNodeResult::Type UTaskGetRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	auto enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	auto blackboardComponent = owner.GetBlackboardComponent();
	auto navigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (blackboardComponent && navigationSystem)
	{
		FNavLocation navLocation;
		navigationSystem->GetRandomReachablePointInRadius(enemyPawn->GetActorLocation(), MaximumDistance, navLocation);
		
		blackboardComponent->SetValueAsVector(PatrolLocationKey.SelectedKeyName, navLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
