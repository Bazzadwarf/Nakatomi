// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiCharacter.h"

// Sets default values
ANakatomiCharacter::ANakatomiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ANakatomiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANakatomiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANakatomiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UHealthComponent* ANakatomiCharacter::GetHealthComponent()
{
	return HealthComponent;
}

void ANakatomiCharacter::SetHealthComponent(UHealthComponent* component)
{
	HealthComponent = component;
}
