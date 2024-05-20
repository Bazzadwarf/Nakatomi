// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "GameFramework/Actor.h"
#include "NakatomiFieldSystemActor.h"
#include "WeaponProperties.h"
#include "WeaponThrowable.h"
#include "NiagaraSystem.h"
#include "Weapon.generated.h"

class ANakatomiCharacter;
class ANakatomiFieldSystemActor;

UENUM()
enum WeaponState
{
	Idle,
	Firing,
	Cooldown,
	Swapping
};

UCLASS(Abstract, Blueprintable)
class NAKATOMI_API AWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* WeaponSkeletalMeshComponent;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANakatomiFieldSystemActor> FieldSystemActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponThrowable> WeaponThrowableTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADecalActor> DecalActor;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* ImpactParticleSystem;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponPickup> PickupTemplate;

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	UFUNCTION(Blueprintable, BlueprintCallable)
	virtual void BeginPlay() override;

public:
	USkeletalMesh* GetSkeletalMesh();

	void SetSkeletalMesh(USkeletalMesh* USkeletalMesh);

	TEnumAsByte<WeaponState>* GetCurrentWeaponStatus();

	void SetCurrentWeaponStatus(TEnumAsByte<WeaponState> NewWeaponStatus);

	FWeaponProperties* GetWeaponProperties();

	void SetWeaponProperties(FWeaponProperties FWeaponProperties);

	ANakatomiCharacter* GetParentPawn();

	void SetParentPawn(ANakatomiCharacter* ANakatomiCharacter);

	USoundBase* GetFireSound();

	void SetFireSound(USoundBase* USoundBase);

	void PlayFireSoundAtLocation(FVector location);

	int GetAmmoCount();

	void SetAmmoCount(int ammoCount);

	void SetAmmoCountToDefault();

	void IncrementAmmoCount(int ammoCount);

	void DecrementAmmoCount(int ammoCount);

	TSubclassOf<class ANakatomiFieldSystemActor> GetFieldSystemActor();

	TSubclassOf<AWeaponThrowable> GetWeaponThrowableTemplate();

	TSubclassOf<class ADecalActor> GetDecalActor();

	UNiagaraSystem* GetImpactParticleSystem();
	
	TSubclassOf<class AWeaponPickup> GetPickupTemplate();
};
