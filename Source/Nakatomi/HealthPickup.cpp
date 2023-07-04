#include "HealthPickup.h"
#include "HealthPickup.h"
#include "PlayerCharacter.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetWorldLocation(this->GetActorLocation());
	StartingLocation = this->GetActorLocation();
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StaticMeshComponent)
	{
		// Rotate Weapon in desired direction
		StaticMeshComponent->AddLocalRotation((SpinRotation * RotationSpeed) * DeltaTime);

		// Bob weapon up and down
		const float Time = GetWorld()->GetRealTimeSeconds();
		const float Sine = FMath::Abs(FMath::Sin(Time * MovementSpeed));
		StaticMeshComponent->SetRelativeLocation(StartingLocation + ((MovementDirection * Sine) * MovementDistance));
	}
}

void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	const auto Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		Player->GetHealthComponent()->IncrementHealth(Health);
	}

	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
