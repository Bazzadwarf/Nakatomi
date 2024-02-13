// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EAIState.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
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

	UAISenseConfig_Sight* SightConfig;

	UAISenseConfig_Hearing* HearingConfig;

	UAISenseConfig_Damage* DamageConfig;

	bool HasAttackToken = false;

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

	UFUNCTION()
	bool TryObtainAttackToken();

	UFUNCTION()
	void TryReleaseAttackToken();

	UFUNCTION()
	bool GetHasAttackToken();

	UFUNCTION()
	void SetState(EAIState state);

	UFUNCTION()
	void SetStateAsPassive();

	UFUNCTION()
	void SetStateAsAttacking(AActor* target);

private:

	void SensedSight(AActor* actor, FAIStimulus& stimulus);
	
	void SensedHearing(AActor* actor, FAIStimulus& stimulus);

	void SensedDamaged(AActor* actor, FAIStimulus& stimulus);
};
