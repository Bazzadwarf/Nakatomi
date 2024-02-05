// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// You can remove these, this is just to get intellisense to work
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>

#include "EnemyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputTriggers.h"
#include "InteractableComponent.h"
#include "NakatomiCMC.h"
#include "WeaponThrowable.h"
#include "GameFramework/CharacterMovementComponent.h"

#define COLLISION_WEAPON	ECC_GameTraceChannel1

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : ANakatomiCharacter(ObjectInitializer)
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
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

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
		currentPlayerHUD = UUserWidget::CreateWidgetInstance(*GetWorld(), PlayerHUD, FName("Player HUD"));

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
			Input->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::BeginJumpCallback);
			Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndJumpCallback);
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

		if (CrouchAction)
		{
			Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::BeginCrouchCallback);
			Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndCrouchCallback);
		}

		if (SlideAction)
		{
			Input->BindAction(SlideAction, ETriggerEvent::Started, this, &APlayerCharacter::BeginSlideCallback);
			Input->BindAction(SlideAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndSlideCallback);
		}

		if (DashAction)
		{
			Input->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::BeginDashCallback);
			Input->BindAction(DashAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndDashCallback);
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

void APlayerCharacter::BeginJumpCallback(const FInputActionInstance& Instance)
{
	Jump();
	jumpPressed = true;
}

void APlayerCharacter::EndJumpCallback(const FInputActionInstance& Instance)
{
	StopJumping();
	jumpPressed = false;
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
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->EnableSprint();
	}

	IsSprinting = true;
}

void APlayerCharacter::SetWalkingCallback(const FInputActionInstance& Instance)
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->DisableSprint();
	}

	IsSprinting = false;
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

			auto staticMeshComponent = Hit.GetActor()->GetComponentByClass<UStaticMeshComponent>();

			if (staticMeshComponent && !staticMeshComponent->IsSimulatingPhysics() && CurrentWeapon->GetDecalActor())
			{
				FTransform transform;
				transform.SetLocation(Hit.ImpactPoint);

				auto decalActor = GetWorld()->SpawnActor<ADecalActor>(CurrentWeapon->GetDecalActor(), transform,
				                                                      SpawnParameters);
				auto rot = Hit.ImpactNormal.Rotation();
				rot.Roll += 90.0f;
				rot.Yaw += 180.0f;
				decalActor->SetActorRotation(rot);
			}
			
			if (staticMeshComponent && !staticMeshComponent->IsSimulatingPhysics() &&
				CurrentWeapon->GetImpactParticleSystem())
			{
				FTransform transform;
				transform.SetLocation(Hit.ImpactPoint);

				UGameplayStatics::SpawnEmitterAtLocation(this,
				                                         CurrentWeapon->GetImpactParticleSystem(),
				                                         transform.GetLocation(),
				                                         FRotator::ZeroRotator,
				                                         true);
			}
		}
	}
}

void APlayerCharacter::OnDamaged()
{
	Super::OnDamaged();
	
	int32 randomAnimMontage = FMath::RandRange(0,OnDamagedHitAnimMontages.Num()-1);
	
	if (OnDamagedHitAnimMontages[randomAnimMontage] != nullptr)
	{
		//TODO: Disable movement while playing animation montage
		PlayAnimMontage(OnDamagedHitAnimMontages[randomAnimMontage]);
	}
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

	// TODO: Move this out into it's own method.
	FString map = GetWorld()->GetMapName();
	map.RemoveFromStart("UEDPIE_0_"); // We have to remove this for reason, I don't fully understand at the moment
	UGameplayStatics::OpenLevel(this, FName(map), false);
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

	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->EnableAds();
	}

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

	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->DisableAds();
	}

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
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController->SetPause(true))
	{
		if (PauseMenuWidget)
		{
			// TODO: Add pause functionality
			currentPauseMenuWidget->AddToViewport();
		}
	}
}

void APlayerCharacter::BeginCrouchCallback(const FInputActionInstance& Instance)
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->EnableCrouch();
	}
}

void APlayerCharacter::EndCrouchCallback(const FInputActionInstance& Instance)
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->DisableCrouch();
	}
}

void APlayerCharacter::BeginSlideCallback(const FInputActionInstance& Instance)
{
	UNakatomiCMC* cmc = GetCharacterMovementComponent();
	if (cmc && !IsThrowing)
	{
		cmc->EnableSlide();
	}
}

void APlayerCharacter::EndSlideCallback(const FInputActionInstance& Instance)
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->DisableSlide();
	}
}

void APlayerCharacter::BeginDashCallback(const FInputActionInstance& Instance)
{
	UNakatomiCMC* cmc = GetCharacterMovementComponent();
	if (cmc && !IsThrowing)
	{
		cmc->EnableDash();
	}
}

void APlayerCharacter::EndDashCallback(const FInputActionInstance& Instance)
{
	if (UNakatomiCMC* cmc = GetCharacterMovementComponent())
	{
		cmc->DisableDash();
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
	if (CurrentWeapon && !IsThrowing)
	{
		IsThrowing = true;
		PlayAnimMontage(ThrowWeaponAnimMontage);
	}
}

void APlayerCharacter::ThrowWeapon()
{
	FVector Location;
	FVector BoxExtent;
	GetActorBounds(true, Location, BoxExtent, false);

	FVector SpawnLocation = (BoxExtent.X * GetActorForwardVector()) * 2;
	SpawnLocation += Location;
	SpawnLocation.Z += BoxExtent.Z;

	TSubclassOf<AWeaponThrowable> WeaponThrowableTemplate = CurrentWeapon->GetWeaponThrowableTemplate();

	AWeaponThrowable* Throwable = GetWorld()->SpawnActor<AWeaponThrowable>(
		WeaponThrowableTemplate, SpawnLocation, FRotator::ZeroRotator);

	Throwable->SetWeaponSkeletalMesh(GetCurrentWeapon()->GetSkeletalMesh());
}

void APlayerCharacter::ThrowExplosiveCallback()
{
	if (ThrowableInventory.Num() > 0)
	{
		IsThrowing = true;
		PlayAnimMontage(ThrowExplosiveAnimMontage);
	}
}

void APlayerCharacter::ThrowExplosive()
{
	FVector Location;
	FVector BoxExtent;
	GetActorBounds(true, Location, BoxExtent, false);
	
	FVector SpawnLocation = (BoxExtent.X * GetActorForwardVector()) * 2; 
	SpawnLocation += Location;
	SpawnLocation += (25.0f * GetActorForwardVector());
	SpawnLocation.Z += BoxExtent.Z;

	GetWorld()->SpawnActor<AThrowable>(ThrowableInventory.Pop(), SpawnLocation, FRotator::ZeroRotator);
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

bool APlayerCharacter::GetPressedJump()
{
	return jumpPressed;
}

bool APlayerCharacter::GetIsThrowing()
{
	return IsThrowing;
}

void APlayerCharacter::SetIsThrowing(bool bIsThrowing)
{
	IsThrowing = bIsThrowing;
}
