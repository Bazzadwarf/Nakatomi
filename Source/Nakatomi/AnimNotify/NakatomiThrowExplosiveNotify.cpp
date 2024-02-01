// Fill out your copyright notice in the Description page of Project Settings.


#include "../AnimNotify/NakatomiThrowExplosiveNotify.h"
#include "Nakatomi/PlayerCharacter.h"

void UNakatomiThrowExplosiveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Character != nullptr)
	{
		Character->ThrowExplosive();
	}
}
