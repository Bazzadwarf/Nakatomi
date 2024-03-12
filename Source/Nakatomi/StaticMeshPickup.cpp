// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshPickup.h"

AStaticMeshPickup::AStaticMeshPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AStaticMeshPickup::BeginPlay()
{
	Super::BeginPlay();
	
	StartingLocation = StaticMeshComponent->GetRelativeLocation();
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));
}

void AStaticMeshPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StaticMeshComponent)
	{
		// Rotate StaticMesh in desired direction
		StaticMeshComponent->AddLocalRotation((SpinRotation * RotationSpeed) * DeltaTime);

		// Bob StaticMesh up and down
		const float Time = GetWorld()->GetRealTimeSeconds();
		const float Sine = FMath::Abs(FMath::Sin(Time * MovementSpeed));
		StaticMeshComponent->SetRelativeLocation(StartingLocation + ((MovementDirection * Sine) * MovementDistance));
	}
}

void AStaticMeshPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
