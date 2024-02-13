// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Nakatomi/EAIState.h"
#include "BTTSetState.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTTSetState : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "New State"))
	EAIState NewState;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;
	
};
