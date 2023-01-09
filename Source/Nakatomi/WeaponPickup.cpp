// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(25.0f, true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);

	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	WeaponComponent = GetWorld()->SpawnActor<AWeapon>(Weapon, SpawnParameters);
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	WeaponComponent->AttachToComponent(RootComponent, TransformRules);
	WeaponComponent->SetActorRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	WeaponComponent->SetActorEnableCollision(false);
	WeaponStartingLocation = WeaponComponent->GetActorLocation();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapBegin);
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate Weapon in desired direction
	WeaponComponent->AddActorLocalRotation((SpinRotation * RotationSpeed) * DeltaTime);

	// Bob weapon up and down
	float Time = GetWorld()->GetRealTimeSeconds();
	float Sine = FMath::Sin(Time * MovementSpeed);
	WeaponComponent->SetActorLocation(WeaponStartingLocation + (MovementDirection * Sine));
}

void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Add weapon to player inventory
	this->Destroy();
	WeaponComponent->Destroy();
}

