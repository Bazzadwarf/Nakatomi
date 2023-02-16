// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Engine/EngineTypes.h"
#include "Components/CapsuleComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& object_initializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto enemy = Cast<AEnemyCharacter>(InPawn);
	check(enemy);

	SetPerceptionComponent(*enemy->GetPerceptionComponent());
	enemy->GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	enemy->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	enemy->GetHealthComponent()->OnDamaged.BindUFunction(this, "OnDamaged");
	enemy->GetHealthComponent()->OnDeath.BindUFunction(this, "OnDeath");
	
	if (auto behaviourTree = enemy->GetBehaviourTree())
	{
		Blackboard->InitializeBlackboard(*behaviourTree->BlackboardAsset);
		BehaviorTree->StartTree(*behaviourTree);
	}

	//ensure(enemy->GetMovementComponent()->UseAccelerationForPathFollowing());
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AEnemyCharacter* AEnemyAIController::GetEnemyCharacter()
{
	return Cast<AEnemyCharacter>(GetCharacter());
}

void AEnemyAIController::OnDamaged(FDamageInfo info)
{
	if (GetEnemyCharacter()->GetHealthComponent()->GetCurrentHealth() > 0.0f)
	{
		// TODO: Do stuff here
	}
}

void AEnemyAIController::OnDeath(FDamageInfo info)
{
	// TODO: Do stuff here

	auto enemy = GetEnemyCharacter();

	enemy->DetachFromControllerPendingDestroy();
	enemy->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	enemy->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	enemy->GetMesh()->SetCollisionProfileName("Ragdoll");
	enemy->SetActorEnableCollision(true);

	enemy->GetMesh()->SetAllBodiesSimulatePhysics(true);
	enemy->GetMesh()->SetSimulatePhysics(true);
	enemy->GetMesh()->WakeAllRigidBodies();
	enemy->GetMesh()->bBlendPhysics = true;

	if (auto characterMovementComponent = enemy->GetCharacterMovement())
	{
		characterMovementComponent->StopMovementImmediately();
		characterMovementComponent->DisableMovement();
		characterMovementComponent->SetComponentTickEnabled(false);
	}

	enemy->SetLifeSpan(10.0f);

	auto weaponPickup = GetWorld()->SpawnActor<AWeaponPickup>();
	weaponPickup->SetActorLocation(enemy->GetActorLocation());
	weaponPickup->SetWeapon(enemy->DefaultWeaponInventory[enemy->GetCurrentInventorySlot()]);
	weaponPickup->SetWeaponProperties(*enemy->CurrentWeapon->GetWeaponProperties());
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& actors)
{
	for (auto actor : actors)
	{
		if (!actor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			continue;
		}

		FActorPerceptionBlueprintInfo perceptionInfo;
		GetPerceptionComponent()->GetActorsPerception(actor, perceptionInfo);

		for (auto& stimulus : perceptionInfo.LastSensedStimuli)
		{
			if (!stimulus.IsValid() || stimulus.IsExpired())
			{
				continue;
			}

			if (stimulus.IsActive())
			{
				PlayerCharacter = Cast<APlayerCharacter>(actor);
				SetFocus(PlayerCharacter, EAIFocusPriority::Gameplay);
			}
			else
			{
				PlayerCharacter = nullptr;
				SetFocus(nullptr, EAIFocusPriority::Gameplay);
			}
		}
	}
}
