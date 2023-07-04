// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponPickup.h"
#include "PlayerCharacter.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

	if (Weapon)
	{
		SpawnWeapon();
	}
}

// Called every frame
void AWeaponPickup::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WeaponComponent)
	{
		// Rotate Weapon in desired direction
		WeaponComponent->AddActorLocalRotation((SpinRotation * RotationSpeed) * DeltaTime);

		// Bob weapon up and down
		const float Time = GetWorld()->GetRealTimeSeconds();
		const float Sine = FMath::Abs(FMath::Sin(Time * MovementSpeed));
		WeaponComponent->SetActorLocation(WeaponStartingLocation + ((MovementDirection * Sine) * MovementDistance));
	}
}

void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	// TODO: Add extra checking here

	const auto Player = Cast<APlayerCharacter>(OtherActor);

	if (Player && Weapon)
	{
		Player->AddWeaponToInventory(Weapon);
		Player->WeaponInventory.Last()->SetWeaponProperties(*WeaponComponent->GetWeaponProperties());
		WeaponComponent->Destroy();
	}

	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeaponPickup::SetWeapon(const TSubclassOf<AWeapon> NewWeapon)
{
	Weapon = NewWeapon;

	if (WeaponComponent)
	{
		WeaponComponent->Destroy();
	}

	SpawnWeapon();
}

FWeaponProperties* AWeaponPickup::GetWeaponProperties()
{
	return &WeaponProperties;
}

void AWeaponPickup::SetWeaponProperties(const FWeaponProperties& FWeaponProperties) const
{
	WeaponComponent->SetWeaponProperties(FWeaponProperties);
}

void AWeaponPickup::SpawnWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	WeaponComponent = GetWorld()->SpawnActor<AWeapon>(Weapon, SpawnParameters);
	const FAttachmentTransformRules TransformRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	WeaponComponent->AttachToComponent(RootComponent, TransformRules);
	WeaponComponent->SetActorRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	WeaponComponent->SetActorEnableCollision(false);

	WeaponStartingLocation = WeaponComponent->GetActorLocation();
	WeaponStartingLocation += ((MovementDirection * MovementDistance) / 2);
}
