// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "NakatomiCharacter.generated.h"

/**
 *
 */
UCLASS()
class NAKATOMI_API ANakatomiCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
	UHealthComponent* HealthComponent = nullptr;

public:
	// Sets default values for this character's properties
	ANakatomiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UHealthComponent* GetHealthComponent();

	void SetHealthComponent(UHealthComponent* healthComponent);
};
