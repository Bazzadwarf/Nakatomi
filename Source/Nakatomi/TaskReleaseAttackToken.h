// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskReleaseAttackToken.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UTaskReleaseAttackToken : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& owner, uint8* memory) override;
};
