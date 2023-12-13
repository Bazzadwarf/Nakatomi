// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTriggerVolume.h"

#include <Kismet/GameplayStatics.h>

#include "PlayerCharacter.h"

void ALevelEndTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	// OnActorBeginOverlap.AddDynamic(this, &ALevelEndTriggerVolume::OnOverlapBegin);
	
}

ALevelEndTriggerVolume::ALevelEndTriggerVolume()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ALevelEndTriggerVolume::OnOverlapBegin);
}

void ALevelEndTriggerVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								   const FHitResult& SweepResult)
{
	// TODO: Add extra functionality!
	if (Cast<APlayerCharacter>(OtherActor))
	{
		GetCollisionComponent()->OnComponentBeginOverlap.Clear();
		
		if (!NextGameLevel.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextGameLevel);	
		}
		
		this->Destroy();
	}
}
