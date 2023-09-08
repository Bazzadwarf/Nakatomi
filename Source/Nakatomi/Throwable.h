// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplosiveActor.h"
#include "Throwable.generated.h"

UCLASS()
class NAKATOMI_API AThrowable : public AExplosiveActor
{
	GENERATED_BODY()

private:

	UPROPERTY()
	USphereComponent* SphereComponent;

public:
	// Sets default values for this actor's properties
	AThrowable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	USphereComponent* GetSphereComponent() const { return SphereComponent; }

};
