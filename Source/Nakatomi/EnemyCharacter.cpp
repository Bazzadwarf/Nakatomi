// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"

AEnemyCharacter::AEnemyCharacter()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	SightConfig->SightRadius = 700.0f;
	SightConfig->LoseSightRadius = 850.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->ConfigureSense(*SightConfig);

	RandomWeaponParameters = CreateDefaultSubobject<URandomWeaponParameters>(TEXT("Random Weapon Parameters"));
	
	GetHealthComponent()->SetMaxHealth(100.0f);

	this->Tags.Add(FName("Enemy"));
}

UBehaviorTree* AEnemyCharacter::GetBehaviourTree()
{
	return BehaviourTree;
}

UAIPerceptionComponent* AEnemyCharacter::GetPerceptionComponent()
{
	return PerceptionComponent;
}

void AEnemyCharacter::OnFire()
{
	TArray<FHitResult> Hits = TArray<FHitResult>();
	CalculateHits(&Hits);
	ProcessHits(Hits);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BANG"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::CalculateHits(TArray<FHitResult>* hits)
{
}

void AEnemyCharacter::ProcessHits(TArray<FHitResult> hits)
{
}
