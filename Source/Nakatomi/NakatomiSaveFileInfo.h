// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakatomiSaveFileInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNakatomiSaveFileInfo
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FString CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FString DateTimeSaved;
};
