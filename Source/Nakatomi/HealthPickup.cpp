#include "HealthPickup.h"
#include "PlayerCharacter.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
