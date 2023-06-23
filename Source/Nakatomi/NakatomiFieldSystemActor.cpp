// Fill out your copyright notice in the Description page of Project Settings.


#include "NakatomiFieldSystemActor.h"

ANakatomiFieldSystemActor::ANakatomiFieldSystemActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(25.0f, true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);

	SphereComponent->SetupAttachment(RootComponent);
	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("Radial Falloff"));
	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("Radial Vector"));
	CullingField = CreateDefaultSubobject<UCullingField>(TEXT("Culling Field"));

	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ANakatomiFieldSystemActor::BeginPlay()
{
	Radius = SphereComponent->GetScaledSphereRadius();
	Position = GetActorLocation();
	RadialFalloff = RadialFalloff->SetRadialFalloff(StrainMagnitude, MinRange, MaxRange, Default, Radius, Position,
	                                                Field_FallOff_None);
	GetFieldSystemComponent()->ApplyPhysicsField(true, Field_ExternalClusterStrain, nullptr, RadialFalloff);

	RadialVector = RadialVector->SetRadialVector(ForceMagnitude, Position);
	CullingField = CullingField->SetCullingField(RadialFalloff, RadialVector, Field_Culling_Outside);
	GetFieldSystemComponent()->ApplyPhysicsField(true, Field_LinearVelocity, nullptr, CullingField);
}
