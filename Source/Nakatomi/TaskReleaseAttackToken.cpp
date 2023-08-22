// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskReleaseAttackToken.h"
#include "EnemyAIController.h"

EBTNodeResult::Type UTaskReleaseAttackToken::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());

	if (enemyController)
	{
		enemyController->TryReleaseAttackToken();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UTaskReleaseAttackToken::AbortTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	return EBTNodeResult::Aborted;
}
