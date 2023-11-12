// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Field/FieldSystemActor.h"
#include <Field/FieldSystemObjects.h>
#include "Field/FieldSystemComponent.h"
#include "NakatomiFieldSystemActor.generated.h"


/**
 * 
 */
UCLASS()
class NAKATOMI_API ANakatomiFieldSystemActor : public AFieldSystemActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USphereComponent* SphereComponent;

	URadialFalloff* RadialFalloff;

	URadialVector* RadialVector;

	UCullingField* CullingField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float StrainMagnitude = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float ForceMagnitude = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float MinRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float MaxRange = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float Default = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	float Radius = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Radial Falloff", Meta = (AllowPrivateAccess = "true"))
	FVector Position = FVector::ZeroVector;

public:
	ANakatomiFieldSystemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
