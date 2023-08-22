// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "StoreActorLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UStoreActorLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UBehaviorTreeComponent* behaviourTreeOwner = nullptr;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector TargetActor;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector TargetActorLocation;

public:
	UStoreActorLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& owner, uint8* memory) override;
};
