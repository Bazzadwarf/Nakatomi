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
	
	if (IsAutomaticOverride)
	{
		weaponProperties.IsAutomatic = IsAutomaticOverride;
	}
	else
	{
		weaponProperties.IsAutomatic = bool(FMath::Rand() % 2);
	}

	return weaponProperties;
}

AWeapon URandomWeaponParameters::GenerateWeapon()
{
	return AWeapon();
}

AWeaponPickup URandomWeaponParameters::GenerateWeaponPickup()
{
	return AWeaponPickup();
}
