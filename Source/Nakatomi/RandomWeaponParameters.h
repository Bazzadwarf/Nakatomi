// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponProperties.h"
#include "WeaponPickup.h"
#include "RandomWeaponParameters.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class NAKATOMI_API URandomWeaponParameters : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float CooldownMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float CooldownMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageMin = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageMax = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Change Time")
	float ChangeTimeMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Change Time")
	float ChangeTimeMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Max Ammo")
	int MaxAmmoMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Max Ammo")
	int MaxAmmoMax = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Ammo")
	int DefaultAmmoMin = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Ammo")
	int DefaultAmmoMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Per Shot")
	int ProjectilePerShotMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Per Shot")
	int ProjectilePerShotMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Range")
	float ProjectileRangeMin = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Range")
	float ProjectileRangeMax = 25000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Spread")
	float WeaponSpreadMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Spread")
	float WeaponSpreadMax = 15.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Is Automatic")
	bool IsAutomaticOverride = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Is Automatic")
	TArray<USkeletalMesh*> WeaponMesh;

	FWeaponProperties GenerateRandomWeaponProperties();

	AWeapon GenerateWeapon();

	AWeaponPickup GenerateWeaponPickup();
};
