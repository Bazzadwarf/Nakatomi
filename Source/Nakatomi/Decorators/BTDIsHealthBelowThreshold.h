// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDIsHealthBelowThreshold.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTDIsHealthBelowThreshold : public UBTDecorator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Current Health Key"))
	FBlackboardKeySelector CurrentHealthKey;

	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "Health Threshold"))
	float HealthThreshold = 25.0f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
