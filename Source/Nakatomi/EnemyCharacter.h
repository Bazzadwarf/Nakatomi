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

protected:
	virtual void BeginPlay() override;
};
