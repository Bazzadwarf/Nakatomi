// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "InteractableComponent.h"

#define COLLISION_WEAPON	ECC_GameTraceChannel1

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer) : ANakatomiCharacter(ObjectInitializer)
{
	RandomWeaponParameters = CreateDefaultSubobject<URandomWeaponParameters>(TEXT("Random Weapon Parameters"));

	GetHealthComponent()->SetMaxHealth(100.0f);

	this->Tags.Add(FName("Enemy"));
}

UBehaviorTree* AEnemyCharacter::GetBehaviourTree()
{
	return BehaviourTree;
}

void AEnemyCharacter::OnFire()
{
	CurrentWeapon->SetCurrentWeaponStatus(Firing);

	TArray<FHitResult> Hits = TArray<FHitResult>();
	CalculateHits(&Hits);
	ProcessHits(Hits);

	CurrentWeapon->PlayFireSoundAtLocation(GetActorLocation());

	PlayOnFireAnimations();

	CurrentWeapon->SetCurrentWeaponStatus(Cooldown);

	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AEnemyCharacter::WeaponCooldownHandler,
	                                CurrentWeapon->GetWeaponProperties()->WeaponCooldown, true);
}

void AEnemyCharacter::WeaponCooldownHandler()
{
	if (CurrentWeapon->GetCurrentWeaponStatus()->GetValue() != Idle)
	{
		CurrentWeapon->SetCurrentWeaponStatus(Idle);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::PlayOnFireAnimations()
{
	Super::PlayOnFireAnimations();
}

void AEnemyCharacter::CalculateHits(TArray<FHitResult>* hits)
{
	// Set up randomness
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float Spread = CurrentWeapon->GetWeaponProperties()->WeaponSpread;
	const float Range = CurrentWeapon->GetWeaponProperties()->ProjectileRange;

	// Calculate starting position and direction
	FVector TraceStart = this->GetTransform().GetLocation();
	FRotator PlayerRot = this->GetTransform().GetRotation().Rotator();
	TraceStart = GetRootComponent()->GetComponentLocation();
	FVector AimDir = PlayerRot.Vector();
	AimDir.Z = 0.0;
	TraceStart = TraceStart + AimDir * ((GetInstigator()->GetActorLocation() - TraceStart) | AimDir);

	// Calculate the hit results from the trace
	TArray<FHitResult> HitResults;

	// Set up the collision query params, use the Weapon trace settings, Ignore the actor firing this trace
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, GetInstigator());
	TraceParams.bReturnPhysicalMaterial = true;

	for (size_t i = 0; i < CurrentWeapon->GetWeaponProperties()->ProjectilesPerShot; i++)
	{
		// Calculate the maximum distance the weapon can fire
		FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, FMath::DegreesToRadians(Spread),
		                                                FMath::DegreesToRadians(Spread));
		FVector MaxHitLoc = TraceStart + (ShootDir * Range);

		GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, MaxHitLoc, COLLISION_WEAPON, TraceParams);

		for (FHitResult Result : HitResults)
		{
			hits->Add(Result);
			DrawDebugLine(GetWorld(), TraceStart, Result.ImpactPoint, FColor::Red, true, 500, 0U, 0);
		}
	}
}

void AEnemyCharacter::ProcessHits(TArray<FHitResult> hits)
{
	for (FHitResult Hit : hits)
	{
		// TODO: Handle hits in a meaningful way
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawn field actor
		FTransform transform;
		transform.SetLocation(Hit.ImpactPoint);
		auto field = GetWorld()->SpawnActor<AFieldSystemActor>(CurrentWeapon->GetFieldSystemActor(), transform,
		                                                       SpawnParameters);

		if (Hit.GetActor())
		{
			if (auto interactableComponent = Hit.GetActor()->GetComponentByClass<UInteractableComponent>())
			{
				interactableComponent->Interact();
			}

			if (auto healthComponent = Hit.GetActor()->GetComponentByClass<UHealthComponent>())
			{
				healthComponent->TakeDamage(Hit.GetActor(), CurrentWeapon->GetWeaponProperties()->WeaponDamage, nullptr,
				                            GetController(), this);
			}
		}
	}
}
