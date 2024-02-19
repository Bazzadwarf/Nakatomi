// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDIsWithinRange.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTDIsWithinRange : public UBTDecorator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "Target Actor Key"))
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Options",
	Meta = (AllowPrivateAccess = "true", DisplayName = "Distance Key"))
	FBlackboardKeySelector DistanceKey;

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
