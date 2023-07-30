// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomWeaponParameters.h"

// Add default functionality here for any IRandomWeaponParameters functions that are not pure virtual.

FWeaponProperties URandomWeaponParameters::GenerateRandomWeaponProperties()
{
	FWeaponProperties weaponProperties = FWeaponProperties();

	weaponProperties.WeaponCooldown = FMath::FRandRange(CooldownMin, CooldownMax);
	weaponProperties.WeaponDamage = FMath::FRandRange(DamageMin, DamageMax);
	weaponProperties.WeaponChangeTime = FMath::FRandRange(ChangeTimeMin, ChangeTimeMax);
	weaponProperties.MaxAmmo = FMath::RandRange(MaxAmmoMin, MaxAmmoMax);
	weaponProperties.DefaultAmmo = FMath::FRandRange(weaponProperties.MaxAmmo * 0.25, weaponProperties.MaxAmmo * 0.75);
	weaponProperties.ProjectilesPerShot = FMath::RandRange(ProjectilePerShotMin, ProjectilePerShotMax);
	weaponProperties.ProjectileRange = FMath::FRandRange(ProjectileRangeMin, ProjectileRangeMax);
	weaponProperties.WeaponSpread = FMath::FRandRange(WeaponSpreadMin, WeaponSpreadMax);
	weaponProperties.ADSWeaponSpreadMultiplier = FMath::FRandRange(ADSWeaponSpreadMulMin, ADSWeaponSpreadMulMax);

	if (IsAutomaticOverride)
	{
		weaponProperties.IsAutomatic = IsAutomaticOverride;
	}
	else
	{
		weaponProperties.IsAutomatic = static_cast<bool>(FMath::Rand() % 2);
	}

	return weaponProperties;
}

USkeletalMesh* URandomWeaponParameters::PickRandomMesh()
{
	// TODO: CHANGE THIS, THIS IS BAD, THIS IS TEMPORARY, GOOD GOD WHY
	if (WeaponMesh.Num() == 0)
	{
		throw;
	}

	return WeaponMesh[FMath::RandRange(0, WeaponMesh.Num() - 1)];
}

USoundBase* URandomWeaponParameters::PickRandomSoundBase()
{
	// TODO: CHANGE THIS, THIS IS BAD, THIS IS TEMPORARY, GOOD GOD WHY
	if (FireSound.Num() == 0)
	{
		return nullptr;
	}

	return FireSound[FMath::RandRange(0, FireSound.Num() - 1)];
}

TSubclassOf<class ANakatomiFieldSystemActor> URandomWeaponParameters::PickRandomFieldSystem()
{
	// TODO: CHANGE THIS, THIS IS BAD, THIS IS TEMPORARY, GOOD GOD WHY
	if (FieldSystemActor.Num() == 0)
	{
		throw;
	}

	return FieldSystemActor[FMath::RandRange(0, FieldSystemActor.Num() - 1)];
}
