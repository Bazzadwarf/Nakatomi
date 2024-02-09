// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tasks/BTTMoveAlongPatrolRoute.h"

#include "navigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Nakatomi/EnemyAIController.h"
#include "Nakatomi/NakatomiCMC.h"

EBTNodeResult::Type UBTTMoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());

	if (enemyPawn->CurrentPatrolRoute)
	{
		FVector location = enemyPawn->CurrentPatrolRoute->GetSplinePointAtWorld();
		UBlackboardComponent* blackboardComponent = owner.GetBlackboardComponent();
		blackboardComponent->SetValueAsVector(PatrolLocationKey.SelectedKeyName, location);

		enemyPawn->CurrentPatrolRoute->IncrementPatrolRoute();
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
