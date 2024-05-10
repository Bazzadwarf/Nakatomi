// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomWeapon.h"

ARandomWeapon::ARandomWeapon()
{
	RandomWeaponParameters = CreateDefaultSubobject<URandomWeaponParameters>(TEXT("Random Weapon Parameters"));
}

void ARandomWeapon::BeginPlay()
{
	WeaponProperties = RandomWeaponParameters->GenerateRandomWeaponProperties();
	WeaponSkeletalMeshComponent->SetSkeletalMeshAsset(RandomWeaponParameters->PickRandomMesh());
	FireSound = RandomWeaponParameters->PickRandomSoundBase();
	FieldSystemActor = RandomWeaponParameters->PickRandomFieldSystem();

	Super::BeginPlay();
}
