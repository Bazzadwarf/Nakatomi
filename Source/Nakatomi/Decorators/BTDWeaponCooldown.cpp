// Fill out your copyright notice in the Description page of Project Settings.


#include "../Decorators/BTDWeaponCooldown.h"

#include "AIController.h"
#include "Nakatomi/EnemyCharacter.h"

void UBTDWeaponCooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (EnemyCharacter && EnemyCharacter->GetCurrentWeapon())
	{
		const float Cooldown = EnemyCharacter->GetCurrentWeapon()->GetWeaponProperties()->WeaponCooldown;
		if (CoolDownTime != Cooldown)
		{
			CoolDownTime = Cooldown;
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
