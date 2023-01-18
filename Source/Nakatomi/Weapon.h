// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class ANakatomiCharacter;

UENUM()
enum WeaponState
{
	Idle,
	Firing,
	Cooldown,
	Swapping
};

USTRUCT(BlueprintType)
struct FWeaponProperties
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	int WeaponDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponChangeTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	int MaxAmmo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	int DefaultAmmo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	int ProjectilesPerShot = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float ProjectileRange = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponSpread = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	bool IsAutomatic = true;
};

UCLASS(Abstract, Blueprintable)
class NAKATOMI_API AWeapon : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<WeaponState> CurrentWeaponStatus;

	UPROPERTY(EditDefaultsOnly)
	FWeaponProperties WeaponProperties;

	UPROPERTY(VisibleAnywhere)
	ANakatomiCharacter* ParentPawn;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FireSound;

	UPROPERTY(VisibleAnywhere)
	int AmmoCount;

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	USkeletalMeshComponent* GetSkeletalMesh();

	void SetSkeletalMesh(USkeletalMeshComponent* USkeletalMeshComponent);

	TEnumAsByte<WeaponState>* GetCurrentWeaponStatus();

	void SetCurrentWeaponStatus(TEnumAsByte<WeaponState> NewWeaponStatus);

	FWeaponProperties* GetWeaponProperties();

	void SetWeaponProperties(FWeaponProperties FWeaponProperties);

	ANakatomiCharacter* GetParentPawn();

	void SetParentPawn(ANakatomiCharacter* ANakatomiCharacter);

	USoundBase* GetFireSound();

	void SetFireSound(USoundBase* USoundBase);

	int GetAmmoCount();

	void SetAmmoCount(int ammoCount);

	void SetAmmoCountToDefault();

	void IncrementAmmoCount(int ammoCount);

	void DecrementAmmoCount(int ammoCount);
};
