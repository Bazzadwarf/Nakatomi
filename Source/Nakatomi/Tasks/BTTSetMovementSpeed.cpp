// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tasks/BTTSetMovementSpeed.h"

#include "Nakatomi/EnemyAIController.h"
#include "Nakatomi/NakatomiCMC.h"

enum class EPatrolMovementEnum : uint8;

EBTNodeResult::Type UBTTSetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(owner.GetAIOwner());
	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());

	switch (MaxWalkSpeedKey)
	{
	case EPatrolMovementEnum::SLOWWALK:
		enemyPawn->GetCharacterMovementComponent()->SetMaxWalkSpeed(slowWalkSpeed);
		break;
	case EPatrolMovementEnum::WALK:
		enemyPawn->GetCharacterMovementComponent()->SetMaxWalkSpeed(walkSpeed);
		break;
	case EPatrolMovementEnum::SPRINT:
		enemyPawn->GetCharacterMovementComponent()->SetMaxWalkSpeed(sprintSpeed);
		break;
	default:
		enemyPawn->GetCharacterMovementComponent()->SetMaxWalkSpeedToDefault();
		break;
	}

	return EBTNodeResult::Succeeded;
}
