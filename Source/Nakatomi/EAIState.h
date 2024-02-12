// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAIState : uint8
{
	PASSIVE UMETA(DisplayName = "Passive"),
	ATTACKING UMETA(DisplayName = "Attacking"),
	FROZEN UMETA(DisplayName = "Frozen"),
	INVESTIGATING UMETA(DisplayName = "Investigating"),
	DEAD UMETA(DisplayName = "Dead"),
};
