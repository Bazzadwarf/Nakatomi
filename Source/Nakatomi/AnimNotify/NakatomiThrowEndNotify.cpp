// Fill out your copyright notice in the Description page of Project Settings.


#include "../AnimNotify/NakatomiThrowEndNotify.h"

#include "Nakatomi/PlayerCharacter.h"

void UNakatomiThrowEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (Character != nullptr)
	{
		Character->SetIsThrowing(false);
	}
}
