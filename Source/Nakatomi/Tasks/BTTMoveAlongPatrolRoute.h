// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTMoveAlongPatrolRoute.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTTMoveAlongPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "Patrol Location Key"))
	FBlackboardKeySelector PatrolLocationKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;
};
