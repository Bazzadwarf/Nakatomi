// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tasks/BTTClearFocus.h"

#include "Nakatomi/EnemyAIController.h"

EBTNodeResult::Type UBTTClearFocus::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	enemyController->ClearFocus(EAIFocusPriority::Default);
	enemyController->SetFocus();
	return EBTNodeResult::Succeeded;
}
