// Fill out your copyright notice in the Description page of Project Settings.


#include "../Decorators/BTDIsHealthBelowThreshold.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UBTDIsHealthBelowThreshold::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	float currentHealth = BlackboardComponent->GetValueAsFloat(CurrentHealthKey.SelectedKeyName);
	
	return currentHealth <= HealthThreshold ? true : false;
}
