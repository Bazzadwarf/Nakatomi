// Fill out your copyright notice in the Description page of Project Settings.


#include "../Decorators/BTDIsWithinRange.h"

#include "AIController.h"
#include "navigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Nakatomi/NakatomiCharacter.h"

bool UBTDIsWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	float Dist = BlackboardComponent->GetValueAsFloat(DistanceKey.SelectedKeyName);
	UObject* Target = BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName);
	auto TargetLocation = Cast<AActor>(Target)->GetActorLocation();
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (pawn && NavigationSystem && TargetLocation != FVector::ZeroVector)
	{
		double Distance = -1.0;
		NavigationSystem->GetPathLength(TargetLocation, pawn->GetTransform().GetLocation(), Distance);
		return Distance <= Dist ? true : false;
	}
	
	return false;
}
