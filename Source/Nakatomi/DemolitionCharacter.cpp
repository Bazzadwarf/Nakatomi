// Fill out your copyright notice in the Description page of Project Settings.


#include "DemolitionCharacter.h"
#include <Kismet/GameplayStatics.h>

#include "EnemyAIController.h"
#include "Engine/OverlapResult.h"

ADemolitionCharacter::ADemolitionCharacter(const FObjectInitializer& ObjectInitializer) : AEnemyCharacter(ObjectInitializer)
{
}

void ADemolitionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetHealthComponent()->OnDeath.BindUFunction(this, "Explode");
	auto controller = Cast<AEnemyAIController>(GetController());
	GetHealthComponent()->OnDeath.BindUFunction(controller, "OnDeath");
	GetHealthComponent()->OnDamaged.BindUFunction(controller, "OnDamaged");
}

void ADemolitionCharacter::Explode()
{
	GetHealthComponent()->TakeDamage(this, this->GetHealthComponent()->GetMaxHealth(), nullptr, nullptr, nullptr);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (ExplosionParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
		                                         ExplosionParticleSystem,
		                                         this->ActorToWorld().GetLocation(),
		                                         FRotator::ZeroRotator,
		                                         true);
	}

	TArray<FOverlapResult> outOverlaps;
	GetWorld()->OverlapMultiByObjectType(outOverlaps,
	                                     ActorToWorld().GetLocation(),
	                                     FQuat::Identity,
	                                     FCollisionObjectQueryParams::AllObjects,
	                                     FCollisionShape::MakeSphere(ExplosionRadius));

	for (FOverlapResult Overlaps : outOverlaps)
	{
		if (auto healthComponent = Overlaps.GetActor()->GetComponentByClass<UHealthComponent>())
		{
			float distance = FVector::Distance(ActorToWorld().GetLocation(),
			                                   Overlaps.GetActor()->ActorToWorld().GetLocation());
			float scale = 1.f - (distance / ExplosionRadius);
			healthComponent->TakeDamage(Overlaps.GetActor(), scale * MaxDamage, nullptr, nullptr, this);
		}
	}

	if (FieldSystemActor)
	{
		FTransform transform;
		transform.SetLocation(this->ActorToWorld().GetLocation());
		auto field = GetWorld()->SpawnActor<AFieldSystemActor>(FieldSystemActor, transform, SpawnParameters);

		if (field)
		{
			field->Destroy();
		}
	}
}
