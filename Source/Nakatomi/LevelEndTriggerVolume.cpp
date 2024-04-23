// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTriggerVolume.h"

#include <Kismet/GameplayStatics.h>

#include "NakatomiGameInstance.h"
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
	UNakatomiGameInstance* gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance)
	{
		int CollectedLevelKeysCount = gameInstance->GetCurrentLevelManager()->GetCollectedLevelKeysCount();
		int InitialLevelKeysCount = gameInstance->GetCurrentLevelManager()->GetInitialLevelKeysCount();
		
		// TODO: Add extra checks!
		if (Cast<APlayerCharacter>(OtherActor) && CollectedLevelKeysCount == InitialLevelKeysCount)
		{
			GetCollisionComponent()->OnComponentBeginOverlap.Clear();

			if (!NextLevel.IsNull())
			{
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);
			}			

			this->Destroy();
		}
	}
}
