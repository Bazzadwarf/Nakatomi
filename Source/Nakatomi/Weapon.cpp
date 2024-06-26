// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AWeapon::AWeapon()
{	
	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	WeaponSkeletalMeshComponent->SetCollisionProfileName(FName("NoCollision"));
	WeaponSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponSkeletalMeshComponent->SetSimulatePhysics(false);
	WeaponSkeletalMeshComponent->SetGenerateOverlapEvents(false);
	WeaponSkeletalMeshComponent->SetNotifyRigidBodyCollision(false);
	SetRootComponent(WeaponSkeletalMeshComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetAmmoCountToDefault();
}

USkeletalMesh* AWeapon::GetSkeletalMesh()
{
	return WeaponSkeletalMeshComponent->GetSkeletalMeshAsset();
}

void AWeapon::SetSkeletalMesh(USkeletalMesh* USkeletalMesh)
{
	WeaponSkeletalMeshComponent->SetSkeletalMeshAsset(USkeletalMesh);
}

TEnumAsByte<WeaponState>* AWeapon::GetCurrentWeaponStatus()
{
	return &CurrentWeaponStatus;
}

void AWeapon::SetCurrentWeaponStatus(TEnumAsByte<WeaponState> NewWeaponStatus)
{
	CurrentWeaponStatus = NewWeaponStatus;
}

FWeaponProperties* AWeapon::GetWeaponProperties()
{
	return &WeaponProperties;
}

void AWeapon::SetWeaponProperties(FWeaponProperties FWeaponProperties)
{
	WeaponProperties = FWeaponProperties;
}

ANakatomiCharacter* AWeapon::GetParentPawn()
{
	return ParentPawn;
}

void AWeapon::SetParentPawn(ANakatomiCharacter* ANakatomiCharacter)
{
	ParentPawn = ANakatomiCharacter;
}

USoundBase* AWeapon::GetFireSound()
{
	return FireSound;
}

void AWeapon::SetFireSound(USoundBase* USoundBase)
{
	FireSound = USoundBase;
}

void AWeapon::PlayFireSoundAtLocation(FVector location)
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, location);
	}
}

int AWeapon::GetAmmoCount()
{
	return AmmoCount;
}

void AWeapon::SetAmmoCount(int ammoCount)
{
	AmmoCount = ammoCount;

	if (AmmoCount > WeaponProperties.MaxAmmo)
	{
		AmmoCount = WeaponProperties.MaxAmmo;
	}
}

void AWeapon::SetAmmoCountToDefault()
{
	AmmoCount = WeaponProperties.DefaultAmmo;
}

void AWeapon::IncrementAmmoCount(int ammoCount)
{
	AmmoCount += ammoCount;

	if (AmmoCount > WeaponProperties.MaxAmmo)
	{
		AmmoCount = WeaponProperties.MaxAmmo;
	}
}

void AWeapon::DecrementAmmoCount(int ammoCount)
{
	AmmoCount -= ammoCount;

	if (AmmoCount < 0)
	{
		AmmoCount = 0;
	}
}

TSubclassOf<AWeaponThrowable> AWeapon::GetWeaponThrowableTemplate()
{
	return WeaponThrowableTemplate;
}

TSubclassOf<ADecalActor> AWeapon::GetDecalActor()
{
	return DecalActor;
}

UNiagaraSystem* AWeapon::GetImpactParticleSystem()
{
	return ImpactParticleSystem;
}

TSubclassOf<AWeaponPickup> AWeapon::GetPickupTemplate()
{
	return PickupTemplate;
}

TSubclassOf<class ANakatomiFieldSystemActor> AWeapon::GetFieldSystemActor()
{
	return FieldSystemActor;
}
