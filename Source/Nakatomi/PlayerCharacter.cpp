// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// You can remove these, this is just to get intellisense to work
#include <Components/CapsuleComponent.h>

#include "InputTriggers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnemyCharacter.h"

#define COLLISION_WEAPON	ECC_GameTraceChannel1

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	//bUseControllerRotationPitch = true;
	//bUseControllerRotationYaw = true;
	//bUseControllerRotationRoll = false;

	// Setup the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->SocketOffset = {0.0f, 75.0f, 110.0f};

	// Setup the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetRelativeRotation({-5.0f, 0.0f, 0.0f});

	// Setup the character movement
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->AirControl = 1.0f;
	CharacterMovementComponent->bOrientRotationToMovement = true;

	// Setup the character perception component
	PerceptionSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Perception Source Stimuli"));
	PerceptionSource->bAutoRegister = true;

	this->Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;

	if (!this->ActorHasTag(FName("Player")))
	{
		this->Tags.Add(FName("Player"));
	}

	if (PlayerHUD)
	{
		currentPlayerHUD = UUserWidget::CreateWidgetInstance(*GetWorld(), PlayerHUD, FName("PLayer HUD"));

		if (currentPlayerHUD)
		{
			currentPlayerHUD->AddToViewport();
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), MappingPriority);
			}
		}
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MovementCallback);
		}

		if (LookAction)
		{
			Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookCallback);
		}

		if (JumpAction)
		{
			Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::JumpCallback);
		}

		if (FireAction)
		{
			Input->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::BeginFireCallback);
			Input->BindAction(FireAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndFireCallback);
		}

		if (QuitAction)
		{
			Input->BindAction(QuitAction, ETriggerEvent::Completed, this, &APlayerCharacter::QuitCallback);
		}

		if (SprintAction)
		{
			Input->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::SetSprintingCallback);
			Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SetWalkingCallback);
		}

		if (WeaponSwitchingAction)
		{
			Input->BindAction(WeaponSwitchingAction, ETriggerEvent::Triggered, this,
			                  &APlayerCharacter::WeaponSwitchingCallback);
		}
	}
}

void APlayerCharacter::MovementCallback(const FInputActionInstance& Instance)
{
	FVector2D vec2 = Instance.GetValue().Get<FVector2D>();

	if (vec2.Size() != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), vec2.Y);
		AddMovementInput(GetActorRightVector(), vec2.X);
	}
}

void APlayerCharacter::LookCallback(const FInputActionInstance& Instance)
{
	FVector2D vec2 = Instance.GetValue().Get<FVector2D>();

	if (vec2.Size() != 0.0f)
	{
		AddControllerYawInput(vec2.X * 45.0f * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput((vec2.Y * (-1.0f)) * 45.0f * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerCharacter::JumpCallback(const FInputActionInstance& Instance)
{
	Jump();
}

void APlayerCharacter::BeginFireCallback(const FInputActionInstance& Instance)
{
	if (CurrentWeapon == nullptr || CurrentWeapon->GetCurrentWeaponStatus()->GetValue() != Idle)
	{
		return;
	}

	IsFiring = true;

	OnFire();

	if (CurrentWeapon == nullptr)
	{
		return;
	}

	if (CurrentWeapon->GetWeaponProperties()->IsAutomatic)
	{
		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &APlayerCharacter::WeaponCooldownHandler,
		                                CurrentWeapon->GetWeaponProperties()->WeaponCooldown, true);
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &APlayerCharacter::OnFire,
		                                CurrentWeapon->GetWeaponProperties()->WeaponCooldown, true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &APlayerCharacter::WeaponCooldownHandler,
		                                CurrentWeapon->GetWeaponProperties()->WeaponCooldown, true);
	}
}

void APlayerCharacter::EndFireCallback(const FInputActionInstance& Instance)
{
	IsFiring = false;
}

void APlayerCharacter::QuitCallback(const FInputActionInstance& Instance)
{
	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}

void APlayerCharacter::SetSprintingCallback(const FInputActionInstance& Instance)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * SprintSpeedMultiplier;
}

void APlayerCharacter::SetWalkingCallback(const FInputActionInstance& Instance)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
}

void APlayerCharacter::CalculateHits(TArray<FHitResult>* hits)
{
	// Set up randomness
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float Spread = CurrentWeapon->GetWeaponProperties()->WeaponSpread;
	const float Range = CurrentWeapon->GetWeaponProperties()->ProjectileRange;

	// TODO: have this start from the end point of the weapon rather than character center
	// Calculate starting position and direction
	FVector TraceStart;
	FRotator PlayerRot;

	APlayerController* Con;
	Con = GetController<APlayerController>();

	if (!Con)
	{
		return;
	}

	Con->GetPlayerViewPoint(TraceStart, PlayerRot);
	TraceStart = GetRootComponent()->GetComponentLocation();
	FVector AimDir = PlayerRot.Vector();
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
			DrawDebugLine(GetWorld(), TraceStart, Result.ImpactPoint, FColor::Blue, true, 500, 0U, 0);
		}
	}
}

void APlayerCharacter::ProcessHits(TArray<FHitResult> hits)
{
	for (FHitResult Hit : hits)
	{
		// TODO: Handle hits in a meaningful way
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawn field actor
		if (CurrentWeapon->GetFieldSystemActor())
		{
			FTransform transform;
			transform.SetLocation(Hit.ImpactPoint);
			auto field = GetWorld()->SpawnActor<AFieldSystemActor>(CurrentWeapon->GetFieldSystemActor(), transform,
			                                                       SpawnParameters);

			if (field)
			{
				field->Destroy();
			}
		}

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

void APlayerCharacter::OnDamaged()
{
	Super::OnDamaged();
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();
	UE_LOG(LogTemp, Error, TEXT("YOU ARE DEAD!"));

	this->DetachFromControllerPendingDestroy();
	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	this->GetMesh()->SetCollisionProfileName("Ragdoll");
	this->SetActorEnableCollision(true);

	this->GetMesh()->SetAllBodiesSimulatePhysics(true);
	this->GetMesh()->SetSimulatePhysics(true);
	this->GetMesh()->WakeAllRigidBodies();
	this->GetMesh()->bBlendPhysics = true;

	if (auto characterMovementComponent = this->GetCharacterMovement())
	{
		characterMovementComponent->StopMovementImmediately();
		characterMovementComponent->DisableMovement();
		characterMovementComponent->SetComponentTickEnabled(false);
	}

	this->SetLifeSpan(10.0f);

	IsFiring = false;
	ClearAllTimers();
}

void APlayerCharacter::WeaponSwitchingCallback(const FInputActionInstance& Instance)
{
	float value = Instance.GetValue().Get<float>();

	if (value > 0)
	{
		InventoryIncrement();
	}
	else
	{
		InventoryDecrement();
	}
}

void APlayerCharacter::OnFire()
{
	if (!IsFiring)
	{
		return;
	}
	
	CurrentWeapon->SetCurrentWeaponStatus(Firing);

	TArray<FHitResult> Hits = TArray<FHitResult>();
	CalculateHits(&Hits);
	ProcessHits(Hits);

	CurrentWeapon->DecrementAmmoCount(1);

	CurrentWeapon->PlayFireSoundAtLocation(this->GetTransform().GetLocation());

	// TODO: Play some animation here

	CurrentWeapon->SetCurrentWeaponStatus(Cooldown);

	if (CurrentWeapon->GetAmmoCount() == 0)
	{
		RemoveCurrentWeaponFromInventory();
	}
}

void APlayerCharacter::WeaponCooldownHandler()
{
	if (CurrentWeapon->GetCurrentWeaponStatus()->GetValue() != Idle)
	{
		CurrentWeapon->SetCurrentWeaponStatus(Idle);
	}

	if (!IsFiring)
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
		GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
	}
}

void APlayerCharacter::ClearAllTimers()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
}

int APlayerCharacter::GetCurrentAmmoCount()
{
	if (CurrentWeapon == nullptr)
	{
		return -1;
	}

	return CurrentWeapon->GetAmmoCount();
}

float APlayerCharacter::GetCurrentHealthCount()
{
	if (!GetHealthComponent())
	{
		return -1;
	}

	return GetHealthComponent()->GetCurrentHealth();
}
