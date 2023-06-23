// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	UBlackboardComponent* Blackboard;

	UBehaviorTreeComponent* BehaviorTree;

	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerception;

public:
	AEnemyAIController(const FObjectInitializer& object_initializer);

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual AEnemyCharacter* GetEnemyCharacter();

	UFUNCTION()
	virtual void OnDamaged(FDamageInfo info);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo info);

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& actors);
};
