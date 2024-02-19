// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Nakatomi/EPatrolMovementEnum.h"
#include "BTTSetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTTSetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Max Walk Speed Key"))
	EPatrolMovementEnum MaxWalkSpeedKey;

private:
	float slowWalkSpeed = 250.0f;
	
	float walkSpeed = 500.0f;

	float sprintSpeed = 750.0f;
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* memory) override;
	
};
