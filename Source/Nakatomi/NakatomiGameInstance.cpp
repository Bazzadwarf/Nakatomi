// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiGameInstance.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UNakatomiAIAttackTokenManager* UNakatomiGameInstance::GetAIAttackTokenManager()
{
	return IsValid(AIAttackTokenManager) ? AIAttackTokenManager : (AIAttackTokenManager = NewObject<UNakatomiAIAttackTokenManager>(this, TEXT("AI Attack Token Manager")));
}

UNakatomiLevelManager* UNakatomiGameInstance::GetCurrentLevelManager()
{
	return IsValid(currentLevelManager)
		       ? currentLevelManager
		       : currentLevelManager = NewObject<UNakatomiLevelManager>(this, TEXT("Level Manager"));
}

void UNakatomiGameInstance::SetCurrentLevelManager(UNakatomiLevelManager* NewLevelManager)
{
	currentLevelManager = NewLevelManager;
}

UNakatomiSaveGame* UNakatomiGameInstance::LoadGameFromSlot(FString SaveSlotName)
{
	if (UNakatomiSaveGame* Save = Cast<UNakatomiSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0)))
	{
		SaveGameObject = Save;
		return SaveGameObject;
	}

	return nullptr;
}

bool UNakatomiGameInstance::SaveGame(bool ResetDefaults)
{
	if (SaveGameObject == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGame called without a loaded save game object."));
		return false;
	}

	if (ResetDefaults)
	{
		SaveGameObject->ResetPlayerValuesToDefault();
	}
	else
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		SaveGameObject->PlayerHealth = Player->GetCurrentHealthCount();
		SaveGameObject->WeaponInventory = Player->WeaponInventory;
		SaveGameObject->CurrentInventorySlot = Player->GetCurrentInventorySlot();
	}

	SaveGameObject->LevelName = GetWorld()->GetMapName();
	SaveGameObject->LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	return UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameObject->PlayerName, 0);
}

UNakatomiSaveGame* UNakatomiGameInstance::GetSaveGameObject()
{
	return SaveGameObject;
}

// TODO: This should either fail or append number if a save already exists with the same name
UNakatomiSaveGame* UNakatomiGameInstance::CreateNewSaveGame(FString PlayerName)
{
	if (UNakatomiSaveGame* Save = Cast<UNakatomiSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UNakatomiSaveGame::StaticClass())))
	{
		Save->PlayerName = PlayerName;

		if (UGameplayStatics::SaveGameToSlot(Save, PlayerName, 0))
		{
			SaveGameObject = Save;
			return SaveGameObject;
		}
	}
	
	return nullptr;
}

TArray<FNakatomiSaveFileInfo> UNakatomiGameInstance::GetAllSaveFilesFromDisk()
{
	TArray<FNakatomiSaveFileInfo> Files;

	IFileManager& FileManager = IFileManager::Get();
	FString SavedGamesFolder = FString{FPaths::ProjectSavedDir()} + "SaveGames/";

	TArray<FString> FileNames;
	FileManager.FindFiles(FileNames, *SavedGamesFolder, TEXT("*.sav"));

	for (FString FileName : FileNames)
	{
		FileName.RemoveFromEnd(".sav");

		if (UNakatomiSaveGame* saveGameObject = Cast<UNakatomiSaveGame>(UGameplayStatics::LoadGameFromSlot(FileName, 0)))
		{
			Files.Add({FileName,
							 saveGameObject->PlayerName,
							 saveGameObject->LevelName,
				FileManager.GetTimeStamp(*(SavedGamesFolder + FileName + ".sav")).ToString()});
		}
	}
	
	return Files;
}
