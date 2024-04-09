// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiCharacter.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "RandomWeaponParameters.h"
#include "Components/WidgetComponent.h"
#include "EnemyCharacter.generated.h"


/**
 * 
 */
UCLASS()
class NAKATOMI_API AEnemyCharacter : public ANakatomiCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	APatrolRoute* CurrentPatrolRoute;

	UPROPERTY(EditAnywhere)
	float AttackRadius = 300.0;

	UPROPERTY(EditAnywhere)
	float DefendRadius = 500.0f;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthbarWidgetComponent;

	UPROPERTY(EditAnywhere)
	float WeaponSpreadModifier = 1.0f;
	
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviourTree;

	UPROPERTY(VisibleAnywhere)
	URandomWeaponParameters* RandomWeaponParameters;

	FTimerHandle CooldownTimerHandle;
	
public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	UBehaviorTree* GetBehaviourTree();

	virtual void OnFire() override;

	void WeaponCooldownHandler();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void PlayOnFireAnimations() override;
	
	virtual void CalculateHits(TArray<FHitResult>* hits, FVector* dir) override;

	virtual void ProcessHits(TArray<FHitResult> hits, FVector dir) override;

protected:
	virtual void OnDamaged() override;
};
