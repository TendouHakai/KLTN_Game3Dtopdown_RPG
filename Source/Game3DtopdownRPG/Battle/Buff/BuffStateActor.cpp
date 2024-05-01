// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffStateActor.h"

ABuffStateActor::ABuffStateActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuffStateActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EndBuffStateActor();
	Super::EndPlay(EndPlayReason);
}

void ABuffStateActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//UpdateBuffTextShow(DeltaSeconds);
}

void ABuffStateActor::ShowBuffStateActor()
{
	Super::ShowBuffStateActor();
	//ShowBuffStringTextureAll();
	ResetParticles();
}

void ABuffStateActor::HideBuffStateActor()
{
	Super::HideBuffStateActor();
	//EndBuffStringTextureAll();

	for (auto& BuffParticleSystemPair : BuffParticleSystems)
	{
		UParticleSystemComponent* ParticleSystemComponent = BuffParticleSystemPair.Value;
		if (false == IsValid(ParticleSystemComponent))
			continue;

		ParticleSystemComponent->SetVisibility(false);
	}
}

void ABuffStateActor::EndBuffStateActor()
{
	Super::EndBuffStateActor();

	//EndBuffStringTextureAll();
	//ShowingBuffTextures.Empty();

	for (auto& BuffParticleSystemPair : BuffParticleSystems)
	{
		UParticleSystemComponent* ParticleSystemComponent = BuffParticleSystemPair.Value;
		if (IsValid(ParticleSystemComponent))
		{
			ParticleSystemComponent->SetTemplate(nullptr);
			ParticleSystemComponent->SetVisibility(false);
			ParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			ParticleSystemComponent->MarkPendingKill();
			ParticleSystemComponent->DestroyComponent();
		}
	}

	BuffParticleSystems.Empty();
	//BuffInfoTextures.Empty();
}

void ABuffStateActor::ResetParticles()
{
	for (auto& BuffParticleSystemPair : BuffParticleSystems)
	{
		UParticleSystemComponent* ParticleSystemComponent = BuffParticleSystemPair.Value;
		if (false == IsValid(ParticleSystemComponent))
			continue;

		ParticleSystemComponent->SetVisibility(true);
		ParticleSystemComponent->ResetParticles(true);
		ParticleSystemComponent->InitializeSystem();
	}
}

EBuffActorType ABuffStateActor::GetBuffActorType()
{
	return EBuffActorType::eBuffStateActor;
}


