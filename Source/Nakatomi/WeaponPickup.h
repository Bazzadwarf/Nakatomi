// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Weapon.h"
#include "WeaponPickup.generated.h"

UCLASS()
class NAKATOMI_API AWeaponPickup : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AWeapon> Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector MovementDirection = FVector(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MovementSpeed = 1.0f;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator SpinRotation = FRotator(0, 1, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RotationSpeed = 1.0f;

private:

	UPROPERTY()
	USphereComponent* SphereComponent;

	UPROPERTY()
	AWeapon* WeaponComponent;

	UPROPERTY()
	FVector WeaponStartingLocation;

public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
