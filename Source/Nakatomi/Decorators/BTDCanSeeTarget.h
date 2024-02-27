// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDCanSeeTarget.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTDCanSeeTarget : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Options",
		Meta = (AllowPrivateAccess = "true", DisplayName = "Target Actor Key"))
	FBlackboardKeySelector TargetActorKey;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
