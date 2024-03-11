// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiLevelManager.h"

#include "NakatomiGameInstance.h"
#include "Kismet/GameplayStatics.h"

UNakatomiLevelManager::UNakatomiLevelManager()
{
	FWorldDelegates::OnPostWorldCreation.AddUObject(this, &UNakatomiLevelManager::BeginPlay);
}

void UNakatomiLevelManager::BeginPlay(UWorld* world)
{
	if (auto gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		gameInstance->SetCurrentLevelManager(this);
	}
}

void UNakatomiLevelManager::LoadNextLevel()
{
	if (!NextLevel.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);	
	}
}
