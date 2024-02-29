// Fill out your copyright notice in the Description page of Project Settings.


#include "GetDistanceToPlayerTask.h"
#include "EnemyAIController.h"


UGetDistanceToPlayerTask::UGetDistanceToPlayerTask()
{
}

EBTNodeResult::Type UGetDistanceToPlayerTask::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	auto enemyPawn = Cast<ADemolitionCharacter>(enemyController->GetPawn());

	if (!enemyPawn || enemyPawn->GetHealthComponent()->GetIsDead())
	{
		return EBTNodeResult::Failed;
	}

	auto blackboardComponent = owner.GetBlackboardComponent();
	auto playerCharacter = Cast<ANakatomiCharacter>(blackboardComponent->GetValueAsObject(TargetActor.SelectedKeyName));
	auto distance = FVector::Distance(enemyPawn->GetActorLocation(), playerCharacter->GetActorLocation());

	if (distance < DistanceThreshold)
	{
		blackboardComponent->SetValueAsBool(IsDeadKey.SelectedKeyName, true);
		enemyPawn->GetHealthComponent()->TakeDamage(enemyPawn, enemyPawn->GetHealthComponent()->GetMaxHealth(), nullptr,
		                                            enemyController, enemyPawn);
		// enemyPawn->Explode();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UGetDistanceToPlayerTask::AbortTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	return EBTNodeResult::Aborted;
}
