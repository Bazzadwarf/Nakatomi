// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThrowable::AThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(25.0f, true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	SphereComponent->SetCollisionProfileName(FName("IgnoreOnlyPawn"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AThrowable::OnOverlapBegin);
	auto playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	auto playerForwardVector = playerCharacter->GetActorForwardVector();
	StaticMeshComponent->AddImpulse(playerForwardVector);
}

void AThrowable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (auto healthComponent = GetComponentByClass<UHealthComponent>())
		{
			healthComponent->TakeDamage(this, healthComponent->GetMaxHealth(), nullptr,
			                            nullptr, this);
		}
	}
}
