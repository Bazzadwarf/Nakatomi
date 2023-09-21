// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Throwable.h"
#include "WeaponThrowable.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API AWeaponThrowable : public AThrowable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponSkeletalMeshComponent;

public:
	// Sets default values for this actor's properties
	AWeaponThrowable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetWeaponSkeletalMesh(USkeletalMesh* SkeletalMesh);
};
