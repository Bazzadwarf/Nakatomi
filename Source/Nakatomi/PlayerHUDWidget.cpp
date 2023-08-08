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
	}
}

void UPlayerHUDWidget::ExpandCrosshair()
{
	if (CrosshairFired)
	{
		auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		float playbackSpeed = 1.0 / player->GetCurrentWeapon()->GetWeaponProperties()->WeaponCooldown;

		PlayAnimation(CrosshairFired, 0.0f, 1, EUMGSequencePlayMode::Forward, playbackSpeed);
	}
}
