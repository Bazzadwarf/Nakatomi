// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveActor.h"
#include <Kismet/GameplayStatics.h>
#include "NakatomiCharacter.h"

// Sets default values
AExplosiveActor::AExplosiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->OnDeath.BindUFunction(this, "Explode");

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AExplosiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AExplosiveActor::Explode()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	if (ExplosionParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
		                                         ExplosionParticleSystem,
		                                         this->ActorToWorld().GetLocation(),
		                                         FRotator::ZeroRotator,
		                                         true);
	}

	TArray<FOverlapResult> outOverlaps;
	GetWorld()->OverlapMultiByObjectType(outOverlaps,
	                                     ActorToWorld().GetLocation(),
	                                     FQuat::Identity,
	                                     FCollisionObjectQueryParams::AllObjects,
	                                     FCollisionShape::MakeSphere(ExplosionRadius));

	for (FOverlapResult Overlaps : outOverlaps)
	{
		UHealthComponent* healthComponent = Overlaps.GetActor()->GetComponentByClass<UHealthComponent>();

		if (healthComponent)
		{
			float distance = FVector::Distance(ActorToWorld().GetLocation(),
			                                   Overlaps.GetActor()->ActorToWorld().GetLocation());
			float scale = 1.f - (distance / ExplosionRadius);
			healthComponent->TakeDamage(Overlaps.GetActor(), scale * MaxDamage, nullptr, nullptr, this);
		}
	}

	if (FieldSystemActor)
	{
		FTransform transform;
		transform.SetLocation(this->ActorToWorld().GetLocation());
		auto field = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemActor, transform, SpawnParameters);

		if (field)
		{
			field->Destroy();
		}
	}

	this->Destroy();
}
