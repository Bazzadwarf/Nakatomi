// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreActorLocationTask.h"
#include "NakatomiCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UStoreActorLocationTask::UStoreActorLocationTask()
{
}

EBTNodeResult::Type UStoreActorLocationTask::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	auto blackboardComponent = owner.GetBlackboardComponent();
	auto playerCharacter = Cast<ANakatomiCharacter>(blackboardComponent->GetValueAsObject(TargetActor.SelectedKeyName));
	
	if (playerCharacter)
	{
		blackboardComponent->SetValueAsVector(TargetActorLocation.SelectedKeyName, playerCharacter->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UStoreActorLocationTask::AbortTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	return EBTNodeResult::Aborted;
}
