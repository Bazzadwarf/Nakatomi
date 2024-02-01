// Fill out your copyright notice in the Description page of Project Settings.


#include "../AnimNotify/NakatomiThrowWeaponNotify.h"

#include "Nakatomi/PlayerCharacter.h"

void UNakatomiThrowWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Character != nullptr)
	{
		Character->ThrowWeapon();
	}
}
