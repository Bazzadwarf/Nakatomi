// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionShape.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.h"
#include "NakatomiFieldSystemActor.h"
#include "ExplosiveActor.generated.h"

UCLASS()
class NAKATOMI_API AExplosiveActor : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANakatomiFieldSystemActor> FieldSystemActor;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionParticleSystem;

	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxDamage = 150.f;

private:

	UPROPERTY(VisibleDefaultsOnly)
	UHealthComponent* HealthComponent = nullptr;


public:	
	// Sets default values for this actor's properties
	AExplosiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void Explode();
};
