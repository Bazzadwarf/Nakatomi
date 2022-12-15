// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

USkeletalMeshComponent* AWeapon::GetSkeletalMesh()
{
	return WeaponSkeletalMesh;
}

void AWeapon::SetSkeletalMesh(USkeletalMeshComponent* USkeletalMeshComponent)
{
	WeaponSkeletalMesh = USkeletalMeshComponent;
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
