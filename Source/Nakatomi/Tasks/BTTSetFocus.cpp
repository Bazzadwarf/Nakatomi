// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tasks/BTTSetFocus.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Nakatomi/EnemyAIController.h"
#include "Nakatomi/PlayerCharacter.h"

EBTNodeResult::Type UBTTSetFocus::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	UBlackboardComponent* BlackboardComponent = owner.GetBlackboardComponent();
	UObject* actor = BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(actor);

	AEnemyAIController* enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	enemyController->SetFocus(PlayerCharacter, EAIFocusPriority::Gameplay);

	return EBTNodeResult::Succeeded;
}
