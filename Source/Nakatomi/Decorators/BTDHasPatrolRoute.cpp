// Fill out your copyright notice in the Description page of Project Settings.


#include "../Decorators/BTDHasPatrolRoute.h"

#include "Nakatomi/EnemyAIController.h"

bool UBTDHasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());

	return enemyPawn->CurrentPatrolRoute ? true : false;
}
