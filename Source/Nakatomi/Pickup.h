// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/PointLightComponent.h>
#include <Components/SphereComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


// TODO: We probably want to add some extra stuff here, particle effects, sounds, etc
UCLASS()
class NAKATOMI_API APickup : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LightFadeSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxLightBrightness = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FColor LightColor = FColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ParticleSystem;

private:
	UPROPERTY()
	USphereComponent* SphereComponent;

	UPROPERTY()
	UPointLightComponent* PointLightComponent;

public:
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
