// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "StaticMeshPickup.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API AStaticMeshPickup : public APickup
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector MovementDirection = FVector(0.0f, 0.0f, 1.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MovementDistance = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MovementSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator SpinRotation = FRotator(0.0, 1.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RotationSpeed = 50.0f;

private:
	UPROPERTY()
	FVector StartingLocation;

public:

	AStaticMeshPickup();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
