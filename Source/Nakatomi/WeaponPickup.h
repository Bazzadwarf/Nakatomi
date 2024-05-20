// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Weapon.h"
#include "Components/WidgetComponent.h"
#include "WeaponPickup.generated.h"

UCLASS()
class NAKATOMI_API AWeaponPickup : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AWeapon> Weapon;

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

	UPROPERTY(EditAnywhere)
	UWidgetComponent* WeaponPropertiesWidgetComponent;
	
private:
	UPROPERTY()
	AWeapon* WeaponComponent;

	UPROPERTY()
	FVector WeaponStartingLocation;

	FWeaponProperties WeaponProperties;

public:
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void SetWeapon(TSubclassOf<AWeapon> NewWeapon);

	FWeaponProperties* GetWeaponProperties();

	void SetWeaponProperties(const FWeaponProperties& FWeaponProperties) const;

private:
	void SpawnWeapon();
};
