#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class NAKATOMI_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
