// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthComponent.h"

#include "EnemyAIController.h"
#include "EnemyCharacter.h"

void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyHealthComponent::TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigatedBy, AActor* damageCauser)
{
	if (damagedActor == nullptr || IsDead || !CanDamage)
	{
		return;
	}

	CurrentHealth -= damage;

	AEnemyCharacter* enemyCharacter = Cast<AEnemyCharacter>(damagedActor);
	UAISense_Damage::ReportDamageEvent(GetWorld(), damagedActor, damageCauser, 1,
	                                   damageCauser->GetTransform().GetLocation(),
	                                   damageCauser->GetTransform().GetLocation());
	
	OnDamaged.ExecuteIfBound({damagedActor, damage, damageType, instigatedBy, damageCauser});

	if (CurrentHealth <= 0.0f)
	{
		IsDead = true;
		OnDeath.ExecuteIfBound({damagedActor, damage, damageType, instigatedBy, damageCauser});
	}
}
