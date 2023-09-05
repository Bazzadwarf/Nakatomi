// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
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
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviourTree;

	UPROPERTY(VisibleAnywhere)
	URandomWeaponParameters* RandomWeaponParameters;

	FTimerHandle CooldownTimerHandle;
	
public:
	AEnemyCharacter();

	UBehaviorTree* GetBehaviourTree();

	virtual void OnFire() override;

	void WeaponCooldownHandler();

protected:
	virtual void BeginPlay() override;

private:
	virtual void CalculateHits(TArray<FHitResult>* hits) override;

	virtual void ProcessHits(TArray<FHitResult> hits) override;
};
