// Fill out your copyright notice in the Description page of Project Settings.


#include "GetDistanceToPlayerTask.h"
#include "EnemyAIController.h"
#include "DemolitionCharacter.h"

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
		enemyPawn->Explode();
		enemyPawn->GetHealthComponent()->TakeDamage(enemyPawn, enemyPawn->GetHealthComponent()->GetMaxHealth(), nullptr, nullptr, nullptr);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UGetDistanceToPlayerTask::AbortTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	return EBTNodeResult::Aborted;
}
