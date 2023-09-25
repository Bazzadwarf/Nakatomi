// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// You can remove these, this is just to get intellisense to work
#include <string>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>

#include "InputTriggers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnemyCharacter.h"
#include "WeaponThrowable.h"


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
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	CameraSpringArmComponent->bDoCollisionTest = true;
	CameraSpringArmComponent->bUsePawnControlRotation = true;
	CameraSpringArmComponent->TargetArmLength = 350.0f;
	CameraSpringArmComponent->bEnableCameraLag = true;
	CameraSpringArmComponent->CameraLagSpeed = 10.0f;
	CameraSpringArmComponent->SocketOffset = {0.0f, 75.0f, 110.0f};

	// Setup the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetRelativeRotation({-5.0f, 0.0f, 0.0f});

	// Setup the camera sights boom
	CameraADSSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraADSSpringArmComponent"));
	CameraADSSpringArmComponent->SetupAttachment(RootComponent);
	CameraADSSpringArmComponent->bDoCollisionTest = true;
	CameraADSSpringArmComponent->bUsePawnControlRotation = true;
	CameraADSSpringArmComponent->TargetArmLength = 100.0f;
	CameraADSSpringArmComponent->bEnableCameraLag = false;
	CameraADSSpringArmComponent->SocketOffset = {0.0f, 50.0f, 75.0f};
	
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

	AimSensitivity = DefaultAimSensitivity;

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

	if (PauseMenuWidget)
	{
		currentPauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidget);
	}
}

void APlayerCharacter::Destroyed()
{
	FString map = GetWorld()->GetMapName();
	map.RemoveFromStart("UEDPIE_0_"); // We have to remove this for reason, I don't fully understand at the moment
	UGameplayStatics::OpenLevel(this, FName(map), false);

	Super::Destroyed();	
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

		if (AimDownSightsAction)
		{
			Input->BindAction(AimDownSightsAction, ETriggerEvent::Started, this,
			                  &APlayerCharacter::BeginAimDownSightsCallback);
			Input->BindAction(AimDownSightsAction, ETriggerEvent::Completed, this,
			                  &APlayerCharacter::EndAimDownSightsCallback);
		}

		if (ThrowWeaponAction)
		{
			Input->BindAction(ThrowWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::ThrowWeaponCallback);
		}

		if (ThrowExplosiveAction)
		{
			Input->BindAction(ThrowExplosiveAction, ETriggerEvent::Started, this,
			                  &APlayerCharacter::ThrowExplosiveCallback);
		}

		if (PauseAction)
		{
			Input->BindAction(PauseAction, ETriggerEvent::Completed, this, &APlayerCharacter::PauseCallback);
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
		AddControllerYawInput(vec2.X * AimSensitivity * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput((vec2.Y * (-1.0f)) * AimSensitivity * GetWorld()->GetDeltaSeconds());
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

	if (CurrentWeapon->GetAmmoCount() == 0)
	{
		ThrowWeaponCallback();
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
	IsSpriting = true;
	
	SetMovementSpeed();
}

void APlayerCharacter::SetWalkingCallback(const FInputActionInstance& Instance)
{
	IsSpriting = false;
	
	SetMovementSpeed();
}

void APlayerCharacter::CalculateHits(TArray<FHitResult>* hits)
{
	// Set up the collision query params, use the Weapon trace settings, Ignore the actor firing this trace
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, GetInstigator());
	TraceParams.bReturnPhysicalMaterial = true;

	// Set up randomness
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float Spread = CurrentWeapon->GetWeaponProperties()->WeaponSpread * WeaponSpreadMultiplier;
	const float Range = CurrentWeapon->GetWeaponProperties()->ProjectileRange;

	FVector CamStart = CameraComponent->GetComponentTransform().GetLocation();
	FVector CamRot = CameraComponent->GetComponentTransform().GetRotation().Vector();
	FVector CamEnd = CamStart + CamRot * 99999.f;

	FHitResult CamHit;
	if (!GetWorld()->LineTraceSingleByChannel(CamHit, CamStart, CamEnd, ECC_Camera))
	{
		return;
	}	

	// TODO: have this start from the end point of the weapon rather than character center
	// Calculate starting position and direction
	FVector TraceStart;
	FRotator PlayerRot;

	GetController<APlayerController>()->GetPlayerViewPoint(TraceStart, PlayerRot);
	TraceStart = GetRootComponent()->GetComponentLocation();
	FVector AimDir = CamHit.ImpactPoint - TraceStart;
	AimDir.Normalize();
	TraceStart = TraceStart + AimDir * ((GetInstigator()->GetActorLocation() - TraceStart) | AimDir);

	// Calculate the hit results from the trace
	TArray<FHitResult> HitResults;

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
				if (!healthComponent->GetIsDead())
				{
					OnEnemyHit.ExecuteIfBound();

					if (HitMarkerSound)
					{
						UGameplayStatics::PlaySound2D(GetWorld(), HitMarkerSound);
					}					
				}
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

void APlayerCharacter::SetMovementSpeed()
{
	if (IsADS)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * ADSSpeedMultiplier;
	}
	else if (IsSpriting)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * SprintSpeedMultiplier;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
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

void APlayerCharacter::BeginAimDownSightsCallback(const FInputActionInstance& Instance)
{
	IsADS = true;

	SetMovementSpeed();

	AimSensitivity = DefaultAimSensitivity * ADSAimSensitivityMultiplier;

	if (CurrentWeapon)
	{
		WeaponSpreadMultiplier = CurrentWeapon->GetWeaponProperties()->ADSWeaponSpreadMultiplier;
	}

	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	CameraComponent->AttachToComponent(CameraADSSpringArmComponent, FAttachmentTransformRules::KeepWorldTransform,
	                                   USpringArmComponent::SocketName);

	UKismetSystemLibrary::MoveComponentTo(CameraComponent, FVector::ZeroVector, FRotator::ZeroRotator, true, true,
	                                      CameraBlendTime,
	                                      true, EMoveComponentAction::Type::Move, LatentActionInfo);
}

void APlayerCharacter::EndAimDownSightsCallback(const FInputActionInstance& Instance)
{
	IsADS = false;

	SetMovementSpeed();

	AimSensitivity = DefaultAimSensitivity;

	WeaponSpreadMultiplier = 1.0f;

	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	CameraComponent->AttachToComponent(CameraSpringArmComponent, FAttachmentTransformRules::KeepWorldTransform,
	                                   USpringArmComponent::SocketName);

	UKismetSystemLibrary::MoveComponentTo(CameraComponent, FVector::ZeroVector, FRotator::ZeroRotator, true, true,
	                                      CameraBlendTime,
	                                      true, EMoveComponentAction::Type::Move, LatentActionInfo);
}

void APlayerCharacter::PauseCallback(const FInputActionInstance& Instance)
{
	if (PauseMenuWidget)
	{
		// TODO: Add pause functionality
	}
}

void APlayerCharacter::OnFire()
{
	if (!IsFiring || CurrentWeapon->GetAmmoCount() == 0)
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

	Super::OnFire();
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
		return 0;
	}

	return CurrentWeapon->GetAmmoCount();
}

float APlayerCharacter::GetCurrentHealthCount()
{
	if (!GetHealthComponent())
	{
		return 0;
	}

	return GetHealthComponent()->GetCurrentHealth();
}

int APlayerCharacter::GetWeaponProjectiles()
{
	if (CurrentWeapon == nullptr)
	{
		return 0;
	}

	return CurrentWeapon->GetWeaponProperties()->ProjectilesPerShot;
}

float APlayerCharacter::GetWeaponCooldown()
{
	if (CurrentWeapon == nullptr)
	{
		return 0;
	}

	return CurrentWeapon->GetWeaponProperties()->WeaponCooldown;
}

float APlayerCharacter::GetWeaponSpread()
{
	if (CurrentWeapon == nullptr)
	{
		return 0;
	}

	return CurrentWeapon->GetWeaponProperties()->WeaponSpread;
}

void APlayerCharacter::ThrowWeaponCallback()
{
	FVector Location;
	FVector BoxExtent;
	GetActorBounds(true, Location, BoxExtent, false);
	
	FVector SpawnLocation = (BoxExtent.X * GetActorForwardVector()) * 2;
	SpawnLocation += Location;
	SpawnLocation.Z += BoxExtent.Z; 
	
	if (TSubclassOf<AWeaponThrowable> WeaponThrowableTemplate = GetCurrentWeapon()->GetWeaponThrowableTemplate())
	{
		AWeaponThrowable* Throwable = GetWorld()->SpawnActor<AWeaponThrowable>(
			WeaponThrowableTemplate, SpawnLocation, FRotator::ZeroRotator);

		Throwable->SetWeaponSkeletalMesh(GetCurrentWeapon()->GetSkeletalMesh());
	}

	RemoveCurrentWeaponFromInventory();
}

void APlayerCharacter::ThrowExplosiveCallback()
{
	if (ThrowableInventory.Num() > 0)
	{
		FVector Location;
		FVector BoxExtent;
		GetActorBounds(true, Location, BoxExtent, false);
	
		FVector SpawnLocation = (BoxExtent.X * GetActorForwardVector()) * 2; 
		SpawnLocation += Location;
		SpawnLocation += (25.0f * GetActorForwardVector());
		SpawnLocation.Z += BoxExtent.Z;

		AThrowable* Throwable = GetWorld()->SpawnActor<AThrowable>(ThrowableInventory.Pop(), SpawnLocation, FRotator::ZeroRotator);
	}
}

AThrowable* APlayerCharacter::ThrowThrowable()
{
	FVector Location;
	FVector BoxExtent;
	GetActorBounds(true, Location, BoxExtent, false);

	FVector SpawnLocation = FVector(Location.Z, Location.Y + (BoxExtent.Y / 2), Location.Z + (BoxExtent.Z / 2));

	if (AThrowable* Throwable = GetWorld()->SpawnActor<AThrowable>(SpawnLocation, FRotator::ZeroRotator))
	{
		return Throwable;
	}

	return nullptr;
}
