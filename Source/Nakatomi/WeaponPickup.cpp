// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponPickup.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/WeaponPickupUserWidget.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
	WeaponPropertiesWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	WeaponPropertiesWidgetComponent->SetupAttachment(RootComponent);
	WeaponPropertiesWidgetComponent->SetRelativeLocation(FVector(0,0,90));
	WeaponPropertiesWidgetComponent->SetTwoSided(true);
	WeaponPropertiesWidgetComponent->SetBackgroundColor(FLinearColor(1,1,1,0));
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

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter && WeaponPropertiesWidgetComponent->GetWidget())
	{
		FVector ActorLocation = GetActorLocation();

		UCameraComponent* PlayerCamera = PlayerCharacter->GetCameraComponent();
		FVector PlayerLocation = PlayerCamera->GetComponentTransform().GetLocation();

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, PlayerLocation);
		WeaponPropertiesWidgetComponent->SetWorldRotation(rotation);
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

	UWeaponPickupUserWidget* userWidget = Cast<UWeaponPickupUserWidget>(WeaponPropertiesWidgetComponent->GetWidget());

	userWidget->AmmoText->SetText(FText::AsNumber(FWeaponProperties.DefaultAmmo));
	
	FString ProjectilesString = FString::FromInt(FWeaponProperties.ProjectilesPerShot);
	ProjectilesString += "x";
	userWidget->ProjectilesText->SetText(FText::FromString(ProjectilesString));

	FString CooldownString = FString::SanitizeFloat(FWeaponProperties.WeaponCooldown);
	CooldownString.LeftInline(3);
	CooldownString += "s";
	userWidget->CooldownText->SetText(FText::FromString(CooldownString));

	FString SpreadString = FString::SanitizeFloat(FWeaponProperties.WeaponSpread);
	SpreadString.LeftInline(4);
	userWidget->SpreadText->SetText(FText::FromString(SpreadString));
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
