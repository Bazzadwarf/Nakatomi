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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Cooldown", DisplayName = "Min")
	float CooldownMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Cooldown", DisplayName = "Max")
	float CooldownMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Damage", DisplayName = "Min")
	float DamageMin = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Damage", DisplayName = "Max")
	float DamageMax = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Change Time", DisplayName = "Min")
	float ChangeTimeMin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Change Time", DisplayName = "Max")
	float ChangeTimeMax = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Max Ammo", DisplayName = "Min")
	int MaxAmmoMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Max Ammo", DisplayName = "Max")
	int MaxAmmoMax = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Default Ammo", DisplayName = "Min")
	int DefaultAmmoMin = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Default Ammo", DisplayName = "Max")
	int DefaultAmmoMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Per Shot", DisplayName = "Min")
	int ProjectilePerShotMin = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Per Shot", DisplayName = "Max")
	int ProjectilePerShotMax = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Range", DisplayName = "Min")
	float ProjectileRangeMin = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Projectile Range", DisplayName = "Max")
	float ProjectileRangeMax = 25000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Weapon Spread", DisplayName = "Min")
	float WeaponSpreadMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Weapon Parameters|Weapon Spread", DisplayName = "Max")
	float WeaponSpreadMax = 15.0f;
	
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
