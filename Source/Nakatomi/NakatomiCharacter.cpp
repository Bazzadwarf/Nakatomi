// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiCharacter.h"

#include "NakatomiCMC.h"

// Sets default values
ANakatomiCharacter::ANakatomiCharacter(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UNakatomiCMC>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NakatomiCMC = Cast<UNakatomiCMC>(GetCharacterMovement());

	// if (!HealthComponent)
	// {
	// 	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	// 	HealthComponent->OnDamaged.BindUFunction(this, "OnDamaged");
	// 	HealthComponent->OnDeath.BindUFunction(this, "OnDeath");
	// }
}

// Called when the game starts or when spawned
void ANakatomiCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetInventoryToDefault();

	NakatomiCMC = Cast<UNakatomiCMC>(GetCharacterMovement());
}

// Called every frame
void ANakatomiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANakatomiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UHealthComponent* ANakatomiCharacter::GetHealthComponent()
{
	return HealthComponent;
}

void ANakatomiCharacter::SetHealthComponent(UHealthComponent* component)
{
	HealthComponent = component;
}

void ANakatomiCharacter::SetInventoryToDefault()
{
	if (WeaponInventory.Num() > 0)
	{
		for (size_t i = 0; i < WeaponInventory.Num(); i++)
		{
			WeaponInventory[i]->Destroy();
		}

		WeaponInventory.Empty();
	}

	for (size_t i = 0; i < DefaultWeaponInventory.Num(); i++)
	{
		if (DefaultWeaponInventory[i])
		{
			AWeapon* weapon = InitializeWeapon(DefaultWeaponInventory[i]);
			WeaponInventory.AddUnique(weapon);
		}
	}

	if (WeaponInventory.Num() > 0)
	{
		CurrentInventorySlot = 0;
		SetCurrentWeapon(WeaponInventory[CurrentInventorySlot]);
	}
}

void ANakatomiCharacter::SelectInventorySlot(int slot)
{
	if (slot < WeaponInventory.Num())
	{
		CurrentInventorySlot = slot;
		SetCurrentWeapon(WeaponInventory[CurrentInventorySlot]);
	}
}

void ANakatomiCharacter::InventoryIncrement()
{
	if (WeaponInventory.Num() > 0)
	{
		SelectInventorySlot((CurrentInventorySlot + 1) % WeaponInventory.Num());
	}
}

void ANakatomiCharacter::InventoryDecrement()
{
	if (WeaponInventory.Num() > 0)
	{
		if (CurrentInventorySlot - 1 < 0)
		{
			SelectInventorySlot(WeaponInventory.Num() - 1);
		}
		else
		{
			SelectInventorySlot((CurrentInventorySlot - 1) % WeaponInventory.Num());
		}
	}
}

void ANakatomiCharacter::RemoveWeaponFromInventory(int i)
{
	if (WeaponInventory[i] == CurrentWeapon)
	{
		CurrentWeapon = nullptr;
	}

	WeaponInventory[i]->Destroy();
	WeaponInventory.RemoveAt(i);

	if (WeaponInventory.Num() == 0)
	{
		CurrentInventorySlot = -1;
	}
	else if (int index = WeaponInventory.Find(CurrentWeapon) == INDEX_NONE)
	{
		SetCurrentWeapon(WeaponInventory[CurrentInventorySlot % WeaponInventory.Num()]);
	}
	else
	{
		CurrentInventorySlot = index;
	}
}

void ANakatomiCharacter::RemoveWeaponFromInventory(AWeapon* weapon)
{
	if (int index = WeaponInventory.Find(weapon) != INDEX_NONE)
	{
		RemoveWeaponFromInventory(index - 1);
	}
}

void ANakatomiCharacter::RemoveCurrentWeaponFromInventory()
{
	RemoveWeaponFromInventory(CurrentWeapon);
}

void ANakatomiCharacter::AddWeaponToInventory(TSubclassOf<class AWeapon> weapon)
{
	if (weapon)
	{
		AWeapon* newWeapon = InitializeWeapon(weapon);
		WeaponInventory.Add(newWeapon);

		if (WeaponInventory.Num() == 1)
		{
			SetCurrentWeapon(WeaponInventory[0]);
		}
	}
}

void ANakatomiCharacter::AddWeaponToInventory(AWeapon* weapon)
{
	weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponHand");
	weapon->SetActorEnableCollision(false);
	weapon->SetActorHiddenInGame(true);
	WeaponInventory.Add(weapon);

	if (WeaponInventory.Num() == 1)
	{
		SetCurrentWeapon(WeaponInventory[0]);
	}
}

AWeapon* ANakatomiCharacter::InitializeWeapon(TSubclassOf<class AWeapon> weapon)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(weapon, SpawnParameters);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponHand");
	Weapon->SetActorEnableCollision(false);
	Weapon->SetActorHiddenInGame(true);

	return Weapon;
}

AWeapon* ANakatomiCharacter::GetCurrentWeapon()
{
	return CurrentWeapon;
}

void ANakatomiCharacter::SetCurrentWeapon(AWeapon* weapon)
{
	if (CurrentWeapon == weapon)
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->SetActorHiddenInGame(true);
	}

	if (weapon)
	{
		CurrentWeapon = weapon;
		CurrentWeapon->SetActorHiddenInGame(false);
	}
}

int ANakatomiCharacter::GetCurrentInventorySlot()
{
	return CurrentInventorySlot;
}

void ANakatomiCharacter::OnFire()
{
	OnFired.ExecuteIfBound();
}

TSubclassOf<AThrowable> ANakatomiCharacter::PopThrowableFromInventory()
{
	if (ThrowableInventory.Num() > 0)
	{
		return ThrowableInventory.Pop();
	}

	return {};
}

void ANakatomiCharacter::PushThrowableToInventory(TSubclassOf<AThrowable> Throwable)
{
	if (ThrowableInventory.Num() < MaximumThrowableInventorySize)
	{
		ThrowableInventory.Push(Throwable);		
	}
}

UNakatomiCMC* ANakatomiCharacter::GetCharacterMovementComponent()
{
	return NakatomiCMC;
}

bool ANakatomiCharacter::GetCrouched()
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		return cmc->IsCrouching();
	}
	
	return false;
}

void ANakatomiCharacter::CalculateHits(TArray<FHitResult>* hits)
{
}

void ANakatomiCharacter::ProcessHits(TArray<FHitResult> hits)
{
}

void ANakatomiCharacter::PlayOnFireAnimations()
{
	if (!GetCrouched())
	{
		PlayAnimMontage(FireWeaponAnimMontage);
	}
}

void ANakatomiCharacter::OnDamaged()
{
}

void ANakatomiCharacter::OnDeath()
{
}
