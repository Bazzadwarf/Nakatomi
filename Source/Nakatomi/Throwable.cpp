// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThrowable::AThrowable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent->SetCollisionProfileName(FName("BlockAll"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	SetRootComponent(StaticMeshComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(25.0f, true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AThrowable::OnOverlapBegin);

	auto playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto playerForwardVector = playerCharacter->GetActorForwardVector();
	playerForwardVector.Z = ImpulseAngle;

	StaticMeshComponent->AddImpulse(playerForwardVector * ImpulseForce);
}

void AThrowable::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->ActorHasTag(FName("Player")) && OtherActor != this)
	{
		if (HealthComponent)
		{
			HealthComponent->TakeDamage(this, HealthComponent->GetMaxHealth(), nullptr,
			                            nullptr, this);
		}
	}
}
