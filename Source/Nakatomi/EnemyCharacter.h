// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include <Perception/AISenseConfig_Sight.h>
#include "RandomWeaponParameters.h"
#include "EnemyCharacter.generated.h"


/**
 * 
 */
UCLASS()
class NAKATOMI_API AEnemyCharacter : public ANakatomiCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* PerceptionComponent;

	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviourTree;

	UPROPERTY(VisibleAnywhere)
	URandomWeaponParameters* RandomWeaponParameters;

public:
	AEnemyCharacter();

	UBehaviorTree* GetBehaviourTree();

	UAIPerceptionComponent* GetPerceptionComponent();

	virtual void OnFire() override;

protected:
	virtual void BeginPlay() override;

private:
	virtual void CalculateHits(TArray<FHitResult>* hits) override;

	virtual void ProcessHits(TArray<FHitResult> hits) override;
};
