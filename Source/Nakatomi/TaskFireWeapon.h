// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskFireWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UTaskFireWeapon : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Options", Meta = (AllowPrivateAccess = "true", DisplayName = "Target Actor Key"))
	FBlackboardKeySelector TargetActor;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;

};
