// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RandomWeaponParameters.h"
#include "Weapon.h"
#include "RandomWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NAKATOMI_API ARandomWeapon : public AWeapon
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Random Weapon Parameters")
	URandomWeaponParameters* RandomWeaponParameters;

public:
	ARandomWeapon();

protected:
	virtual void BeginPlay() override;
};
