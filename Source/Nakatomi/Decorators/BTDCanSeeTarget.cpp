// Fill out your copyright notice in the Description page of Project Settings.


#include "../Decorators/BTDCanSeeTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDCanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FHitResult HitResult;
	
	FVector Start = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
	FVector End = TargetActor->GetActorLocation();

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn);

	if (HitResult.GetActor())
	{
		return true;
	}

	return false;
}
