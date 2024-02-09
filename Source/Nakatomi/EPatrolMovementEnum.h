// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPatrolMovementEnum : uint8
{
	SLOWWALK UMETA(DisplayName = "Slow Walk"),
	WALK UMETA(DisplayName = "Walk"),
};
