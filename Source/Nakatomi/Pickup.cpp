// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include <Kismet/GameplayStatics.h>

#include "PlayerCharacter.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(25.0f, true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	SetRootComponent(SphereComponent);

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	PointLightComponent->SetLightColor(FLinearColor::FromSRGBColor(LightColor));
	PointLightComponent->SetWorldLocation(this->GetActorLocation());
}

// Called every frame
void APickup::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	PointLightComponent->MarkRenderStateDirty();
	// We have to do this because Unreal doesn't like it when you create lights in c++ apparently ::pain::
	const float Sin = FMath::Abs(FMath::Sin(GetWorld()->GetRealTimeSeconds() * (LightFadeSpeed / 2)));
	//PointLightComponent->SetLightBrightness(sin * MaxLightBrightness);
	//PointLightComponent->SetLightBrightness(Sin * MaxLightBrightness);
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		if (OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OverlapSound, this->ActorToWorld().GetLocation());
		}

		if (ParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,
			                                         ParticleSystem,
			                                         this->ActorToWorld().GetLocation(),
			                                         FRotator::ZeroRotator,
			                                         true);
		}

		this->Destroy();
	}
}
