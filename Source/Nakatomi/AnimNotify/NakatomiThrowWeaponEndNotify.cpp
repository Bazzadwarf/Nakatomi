// Fill out your copyright notice in the Description page of Project Settings.


#include "../AnimNotify/NakatomiThrowWeaponEndNotify.h"
#include "Nakatomi/PlayerCharacter.h"

void UNakatomiThrowWeaponEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Character != nullptr)
	{
		Character->RemoveCurrentWeaponFromInventory();
	}
}
