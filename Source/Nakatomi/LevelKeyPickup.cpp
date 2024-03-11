// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelKeyPickup.h"

#include "NakatomiGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ALevelKeyPickup::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		gameInstance->GetCurrentLevelManager()->IncrementInitialLevelKeys();
	}
}

void ALevelKeyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelKeyPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		gameInstance->GetCurrentLevelManager()->IncrementInitialLevelKeys();
	}
	
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
