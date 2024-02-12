// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include <Kismet/GameplayStatics.h>

#include "EAIState.h"
#include "NakatomiGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& object_initializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	AIPerception = PerceptionComponent;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense Config"));
	SightConfig->SightRadius = 700.0f;
	SightConfig->LoseSightRadius = 850.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerception->ConfigureSense(*SightConfig);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto enemy = Cast<AEnemyCharacter>(InPawn);
	check(enemy);

	SetPerceptionComponent(*PerceptionComponent);
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	enemy->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	enemy->GetHealthComponent()->OnDamaged.BindUFunction(this, "OnDamaged");
	enemy->GetHealthComponent()->OnDeath.BindUFunction(this, "OnDeath");

	if (auto behaviourTree = enemy->GetBehaviourTree())
	{
		Blackboard->InitializeBlackboard(*behaviourTree->BlackboardAsset);
		BehaviorTree->StartTree(*behaviourTree);
		Blackboard->SetValueAsObject("SelfActor", enemy);
	}

	Blackboard->SetValueAsEnum("State",  static_cast<uint8>(EAIState::PASSIVE));
	
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
	enemy->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

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

	if (enemy->DefaultWeaponInventory.Num() > 0)
	{
		// TODO: This can sometimes crash, need to investigate
		if (auto weaponPickup = GetWorld()->SpawnActor<AWeaponPickup>())
		{
			weaponPickup->SetActorLocation(enemy->GetActorLocation());
			weaponPickup->SetWeapon(enemy->DefaultWeaponInventory[enemy->GetCurrentInventorySlot()]);
			weaponPickup->SetWeaponProperties(*enemy->CurrentWeapon->GetWeaponProperties());			
		}
	}
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
		PerceptionComponent->GetActorsPerception(actor, perceptionInfo);

		for (auto& stimulus : perceptionInfo.LastSensedStimuli)
		{
			if (!stimulus.IsValid() || stimulus.IsExpired())
			{
				continue;
			}

			Blackboard->SetValueAsObject("TargetActor", actor);

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

bool AEnemyAIController::TryObtainAttackToken()
{
	if (HasAttackToken)
	{
		return true;
	}

	if (auto gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		HasAttackToken = gameInstance->GetAIAttackTokenManager()->RequestToken();
	}

	return false;
}

void AEnemyAIController::TryReleaseAttackToken()
{
	if (HasAttackToken)
	{
		if (auto gameInstance = Cast<UNakatomiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			HasAttackToken = gameInstance->GetAIAttackTokenManager()->ReleaseToken();
		}
	}
}

bool AEnemyAIController::GetHasAttackToken()
{
	return HasAttackToken;
}

void AEnemyAIController::SetState(EAIState state)
{
	Blackboard->SetValueAsEnum("State",  static_cast<uint8>(state));
}

void AEnemyAIController::SetStateAsPassive()
{
	SetState(EAIState::PASSIVE);
}

void AEnemyAIController::SetStateAsAttacking(AActor* target)
{
	Blackboard->SetValueAsObject("TargetActor", target);
	SetState(EAIState::ATTACKING);
}
