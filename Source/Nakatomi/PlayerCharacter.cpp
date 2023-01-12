// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// You can remove these, this is just to get intellisense to work
#include "InputTriggers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"

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
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->SocketOffset = { 0.0f, 0.0f, 220.0f };

	// Setup the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetRelativeRotation({ -10.0f,0.0f,0.0f });

	// Setup the character movement
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->AirControl = 1.0f;
	CharacterMovementComponent->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SetInventoryToDefault();
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
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
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
			Input->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::FireCallback);
		}

		if (QuitAction)
		{
			Input->BindAction(QuitAction, ETriggerEvent::Started, this, &APlayerCharacter::QuitCallback);
		}

		if (SprintAction)
		{
			Input->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::SetSprintingCallback);
			Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SetWalkingCallback);
		}

		if (WeaponSwitchingAction)
		{
			Input->BindAction(WeaponSwitchingAction, ETriggerEvent::Triggered, this, &APlayerCharacter::WeaponSwitchingCallback);
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

void APlayerCharacter::FireCallback(const FInputActionInstance& Instance)
{
	// TODO: Add extra gun fire logic

	// Calculate hits from hitscan
	TArray<FHitResult> Hits = TArray<FHitResult>();
	CalculateHits(&Hits);
}

void APlayerCharacter::QuitCallback(const FInputActionInstance& Instance)
{
	FGenericPlatformMisc::RequestExit(true);
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
	const float Spread = 1.0f; // TODO: Replace with a more sensible value later
	const float Range = 50000.f; // TODO: Replace with a more sensible value later

	// Calculate starting position and direction
	FVector TraceStart;
	FRotator PlayerRot;
	GetController<APlayerController>()->GetPlayerViewPoint(TraceStart, PlayerRot);
	TraceStart = GetRootComponent()->GetComponentLocation();
	FVector AimDir = PlayerRot.Vector();
	AimDir.Z = 0.0;
	TraceStart = TraceStart + AimDir * ((GetInstigator()->GetActorLocation() - TraceStart) | AimDir);

	// Calculate the hit results from the trace
	TArray<FHitResult> HitResults;

	/// Set up the collision query params, use the Weapon trace settings, Ignore the actor firing this trace
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, GetInstigator());
	TraceParams.bReturnPhysicalMaterial = true;

	/// Calculate the maximum distance the weapon can fire
	FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, FMath::DegreesToRadians(Spread), FMath::DegreesToRadians(Spread));
	FVector MaxHitLoc = TraceStart + (ShootDir * Range);

	GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, MaxHitLoc, COLLISION_WEAPON, TraceParams);

	for (FHitResult Result : HitResults)
	{
		hits->Add(Result);
		DrawDebugLine(GetWorld(), TraceStart, Result.ImpactPoint, FColor::Blue, true, 500, 0U, 0);

		// TODO: Handle hits in a meaningful way
	}
}

void APlayerCharacter::SetInventoryToDefault()
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

void APlayerCharacter::SelectInventorySlot(int slot)
{	
	if (slot < WeaponInventory.Num())
	{
		CurrentInventorySlot = slot;
		SetCurrentWeapon(WeaponInventory[CurrentInventorySlot]);
	}
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

void APlayerCharacter::InventoryIncrement()
{
	if (WeaponInventory.Num() > 0)
	{
		SelectInventorySlot((CurrentInventorySlot + 1) % WeaponInventory.Num());
	}
}

void APlayerCharacter::InventoryDecrement()
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

AWeapon* APlayerCharacter::InitializeWeapon(TSubclassOf<class AWeapon> weapon)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(weapon, SpawnParameters);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponHand");
	Weapon->SetActorEnableCollision(false);
	Weapon->SetActorHiddenInGame(true);
	
	return Weapon;
}

AWeapon* APlayerCharacter::GetCurrentWeapon()
{
	return CurrentWeapon;
}

void APlayerCharacter::SetCurrentWeapon(AWeapon* weapon)
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

void APlayerCharacter::AddWeaponToInventory(TSubclassOf<class AWeapon> weapon)
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

void APlayerCharacter::RemoveWeaponFromInventory(int i)
{
	// TODO: Add more checking here
	WeaponInventory[i]->Destroy();
	WeaponInventory.RemoveAt(i);
}

void APlayerCharacter::RemoveCurrentWeaponFromInventory()
{
	// TODO: Add more checking here

}
