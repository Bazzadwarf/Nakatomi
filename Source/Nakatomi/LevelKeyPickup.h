// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshPickup.h"
#include "LevelKeyPickup.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API ALevelKeyPickup : public AStaticMeshPickup
{
	GENERATED_BODY()

public:
	ALevelKeyPickup() {	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
