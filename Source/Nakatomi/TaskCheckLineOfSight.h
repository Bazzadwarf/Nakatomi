// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskCheckLineOfSight.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UTaskCheckLineOfSight : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Self Actor Key"))
	FBlackboardKeySelector SelfActorKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;
};
