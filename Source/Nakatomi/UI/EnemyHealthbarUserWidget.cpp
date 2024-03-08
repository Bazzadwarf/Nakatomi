// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/EnemyHealthbarUserWidget.h"

#include "Nakatomi/EnemyCharacter.h"

void UEnemyHealthbarUserWidget::BindOwner(AEnemyCharacter* NewOwner)
{
	Owner = NewOwner;
	
	if (Owner)
	{
		auto healthComponent = Owner->GetHealthComponent(); 
		healthComponent->OnDamaged.BindUFunction(this, "UpdateHealthbar");		
	}
}

void UEnemyHealthbarUserWidget::UpdateHealthbar()
{
	if (Owner)
	{
		float percent = Owner->GetHealthComponent()->GetCurrentHealth() / Owner->GetHealthComponent()->GetMaxHealth();
		Healthbar->SetPercent(percent); 		
	}
}
