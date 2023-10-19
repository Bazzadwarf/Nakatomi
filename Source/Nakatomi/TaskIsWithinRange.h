// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskIsWithinRange.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UTaskIsWithinRange : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Source Location Key"))
	FBlackboardKeySelector SourceLocationKey;

	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Self Actor Key"))
	FBlackboardKeySelector SelfActorKey;
	
	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "Maximum Distance"))
	float MaximumDistance = 500.0f;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;

	
};
