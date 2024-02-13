// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tasks/BTTSetState.h"

#include "Nakatomi/EnemyAIController.h"

EBTNodeResult::Type UBTTSetState::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(owner.GetAIOwner()))
	{
		EnemyController->SetState(NewState);	
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
