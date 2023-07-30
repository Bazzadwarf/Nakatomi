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
class NAKATOMI_API URandomWeaponParameters : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Cooldown", DisplayName = "Min",
		meta = ( ClampMin = "0", ClampMax = "5" ))
	float CooldownMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Cooldown", DisplayName = "Max",
		meta = ( ClampMin = "0", ClampMax = "5"))
	float CooldownMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Damage", DisplayName = "Min",
		meta = ( ClampMin = "0" ))
	float DamageMin = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Damage", DisplayName = "Max",
		meta = ( ClampMin = "0"))
	float DamageMax = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Change Time", DisplayName = "Min",
		meta = ( ClampMin = "0", ClampMax = "5" ))
	float ChangeTimeMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Change Time", DisplayName = "Max",
		meta = ( ClampMin = "0", ClampMax = "5" ))
	float ChangeTimeMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Max Ammo", DisplayName = "Min",
		meta = ( ClampMin = "0" ))
	int MaxAmmoMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Max Ammo", DisplayName = "Max",
		meta = ( ClampMin = "0" ))
	int MaxAmmoMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Default Ammo", DisplayName = "Min",
		meta = ( ClampMin = "0" ))
	int DefaultAmmoMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Default Ammo", DisplayName = "Max")
	int DefaultAmmoMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Per Shot",
		DisplayName = "Min", meta = ( ClampMin = "0", ClampMax = "50" ))
	int ProjectilePerShotMin = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Per Shot",
		DisplayName = "Max", meta = ( ClampMin = "0", ClampMax = "50" ))
	int ProjectilePerShotMax = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Range",
		DisplayName = "Min", meta = ( ClampMin = "0", ClampMax = "1000000" ))
	float ProjectileRangeMin = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Range",
		DisplayName = "Max", meta = ( ClampMin = "0", ClampMax = "1000000" ))
	float ProjectileRangeMax = 25000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Weapon Spread",
		DisplayName = "Min", meta = ( ClampMin = "0", ClampMax = "360" ))
	float WeaponSpreadMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Weapon Spread",
		DisplayName = "Max", meta = ( ClampMin = "0", ClampMax = "360" ))
	float WeaponSpreadMax = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|ADS Weapon Spread Multiplier",
		DisplayName = "Min", meta = (ClampMin = "0", ClampMax = "360"))
	float ADSWeaponSpreadMulMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|ADS Weapon Spread Multiplier",
		DisplayName = "Max", meta = (ClampMin = "0", ClampMax = "360"))
	float ADSWeaponSpreadMulMax = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Is Automatic")
	bool IsAutomaticOverride = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Meshes")
	TArray<USkeletalMesh*> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Fire Sounds")
	TArray<USoundBase*> FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Field System Actor")
	TArray<TSubclassOf<class ANakatomiFieldSystemActor>> FieldSystemActor;

	FWeaponProperties GenerateRandomWeaponProperties();

	USkeletalMesh* PickRandomMesh();

	USoundBase* PickRandomSoundBase();

	TSubclassOf<class ANakatomiFieldSystemActor> PickRandomFieldSystem();
};
