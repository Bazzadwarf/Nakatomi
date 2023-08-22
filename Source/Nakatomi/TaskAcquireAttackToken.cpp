// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAcquireAttackToken.h"
#include "EnemyAIController.h"

EBTNodeResult::Type UTaskAcquireAttackToken::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());

	if (enemyController->TryObtainAttackToken())
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UTaskAcquireAttackToken::AbortTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	return EBTNodeResult::Aborted;
}
