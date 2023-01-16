// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructable.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADestructable::ADestructable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	this->Tags.Add(FName("Destructable"));
}

// Called when the game starts or when spawned
void ADestructable::BeginPlay()
{
	Super::BeginPlay();

	if (!this->ActorHasTag(FName("Destructable")))
	{
		this->Tags.Add(FName("Destructable"));
	}
}

void ADestructable::Destruct()
{
	// TODO: Add some more logic here
	
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleEffect, this->ActorToWorld().GetLocation(), FRotator::ZeroRotator, true);
	Destroy();
}
