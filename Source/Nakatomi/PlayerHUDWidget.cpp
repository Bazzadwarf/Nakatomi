// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCharacter.h"

void UPlayerHUDWidget::NativeConstruct()
{
	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player)
	{
		player->OnFired.BindUFunction(this, "ExpandCrosshair");
		player->OnEnemyHit.BindUFunction(this, "ShowHitMarker");
	}
}

void UPlayerHUDWidget::ExpandCrosshair()
{
	if (CrosshairFired)
	{
		if (auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			float playbackSpeed = 1.0 / player->GetCurrentWeapon()->GetWeaponProperties()->WeaponCooldown;

			PlayAnimation(CrosshairFired, 0.0f, 1, EUMGSequencePlayMode::Forward, playbackSpeed);
		}
	}
}

void UPlayerHUDWidget::ShowHitMarker()
{
	if (RevealHitmarker)
	{
		PlayAnimation(RevealHitmarker, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

FString UPlayerHUDWidget::GetHealthbarText(APlayerCharacter* PlayerCharacter)
{
	int healthbarCharacters = 5;
	float normalised = PlayerCharacter->GetHealthComponent()->GetCurrentHealth() /
					   PlayerCharacter->GetHealthComponent()->GetMaxHealth();
	float adjusted = normalised * healthbarCharacters;
	int segments = FMath::RoundToInt(adjusted);
	
	FString healthBar = FString("[");

	for (int i = 0; i < segments; i++)
	{
		healthBar.Append("=");
	}

	for (int i = segments; i < healthbarCharacters; i++)
	{
		healthBar.Append(" ");
	}

	healthBar.Append("]");
	
	return healthBar;
}
