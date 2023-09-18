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
