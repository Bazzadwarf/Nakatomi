// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponThrowable.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AWeaponThrowable::AWeaponThrowable()
{
	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	WeaponSkeletalMeshComponent->SetCollisionProfileName(FName("BlockAll"));
	WeaponSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponSkeletalMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponSkeletalMeshComponent->SetSimulatePhysics(true);
	WeaponSkeletalMeshComponent->SetGenerateOverlapEvents(true);
	WeaponSkeletalMeshComponent->SetNotifyRigidBodyCollision(true);
	SetRootComponent(WeaponSkeletalMeshComponent);
}

void AWeaponThrowable::BeginPlay()
{
	Super::BeginPlay();

	WeaponSkeletalMeshComponent->OnComponentHit.AddDynamic(this, &AWeaponThrowable::OnOverlapBegin);

	auto playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto playerForwardVector = playerCharacter->GetActorForwardVector();
	playerForwardVector.Z = ImpulseAngle;

	WeaponSkeletalMeshComponent->AddImpulse(playerForwardVector * ImpulseForce);
}

void AWeaponThrowable::SetWeaponSkeletalMesh(USkeletalMesh* SkeletalMesh)
{
	WeaponSkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	if (auto playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		auto playerForwardVector = playerCharacter->GetActorForwardVector();
		playerForwardVector.Z = ImpulseAngle;

		WeaponSkeletalMeshComponent->AddImpulse(playerForwardVector * ImpulseForce);
	}
}
