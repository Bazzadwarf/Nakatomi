// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

UCLASS()
class NAKATOMI_API APatrolRoute : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	USplineComponent* Spline;

private:
	int PatrolIndex = 0;

	int Direction;
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();

	void IncrementPatrolRoute();

	FVector GetSplinePointAtWorld(int pointIndex);
};
