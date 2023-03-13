// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskFireWeapon.h"
#include "EnemyAIController.h"

EBTNodeResult::Type UTaskFireWeapon::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	auto enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	auto blackboardComponent = owner.GetBlackboardComponent();
	auto playerCharacter = Cast<APlayerCharacter>(blackboardComponent->GetValueAsObject(TargetActor.SelectedKeyName));

	if (enemyPawn && playerCharacter)
	{
		enemyPawn->OnFire();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
