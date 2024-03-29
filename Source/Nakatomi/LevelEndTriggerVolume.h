// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LevelEndTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API ALevelEndTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLevel;
	
protected:
	virtual void BeginPlay() override;

public:
	ALevelEndTriggerVolume();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								   const FHitResult& SweepResult);
};
