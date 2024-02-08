// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
}

void APatrolRoute::IncrementPatrolRoute()
{
	if (PatrolIndex == Spline->GetNumberOfSplinePoints() - 1)
	{
		Direction = -1;
	}
	else if (PatrolIndex == 0)
	{
		Direction = 1;
	}
	
	PatrolIndex += Direction;


}

FVector APatrolRoute::GetSplinePointAtWorld(int pointIndex)
{
	return Spline->GetLocationAtSplinePoint(pointIndex, ESplineCoordinateSpace::World);
}
