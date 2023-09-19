// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponThrowable.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AWeaponThrowable::AWeaponThrowable()
{
	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	WeaponSkeletalMeshComponent->SetCollisionProfileName(FName("PhysicsActor"));
	WeaponSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponSkeletalMeshComponent->SetSimulatePhysics(true);
	SetRootComponent(WeaponSkeletalMeshComponent);
}

void AWeaponThrowable::BeginPlay()
{
	Super::BeginPlay();
	
	auto playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto playerForwardVector = playerCharacter->GetActorForwardVector();
	playerForwardVector.Z = ImpulseAngle;
	WeaponSkeletalMeshComponent->AddImpulse(playerForwardVector * ImpulseForce);
}

void AWeaponThrowable::SetWeaponSkeletalMesh(USkeletalMesh* SkeletalMesh)
{
	WeaponSkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	
	auto playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto playerForwardVector = playerCharacter->GetActorForwardVector();
	playerForwardVector.Z = ImpulseAngle;
	WeaponSkeletalMeshComponent->AddImpulse(playerForwardVector * ImpulseForce);
}
