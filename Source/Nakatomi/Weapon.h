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

USTRUCT()
struct FWeaponProperties
{
	GENERATED_USTRUCT_BODY()

	float WeaponCooldown = 1.0f;

	int WeaponDamage = 10;

	float WeaponChangeTime = 2.0f;

	int ProjectilesPerShot = 1;

	float ProjectileRange = 10000.0f;

	float WeaponSpread = 2.5f;

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
};
