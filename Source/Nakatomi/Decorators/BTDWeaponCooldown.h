// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Cooldown.h"
#include "BTDWeaponCooldown.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API UBTDWeaponCooldown : public UBTDecorator_Cooldown
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
