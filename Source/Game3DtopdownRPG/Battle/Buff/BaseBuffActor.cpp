// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuffActor.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "BaseBuff.h"
#include "Particles/ParticleSystemComponent.h"
#include "BuffStruct.h"

ABaseBuffActor::ABaseBuffActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseBuffActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseBuffActor::InitBuffStateActor(ABaseCharacter* InOwner, UBaseBuff* BaseBuff)
{
	if (false == IsValid(InOwner))
		return;

	OwnerCharacter = InOwner;

	AttachToActor(OwnerCharacter, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	InitBuffStateActorBP();
}

void ABaseBuffActor::EndBuffStateActor()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	Destroy();
	OwnerCharacter = nullptr;
}

EBuffActorType ABaseBuffActor::GetBuffActorType()
{
	return EBuffActorType::Max;
}

void ABaseBuffActor::AddBuffInfo(UBaseBuff* BaseBuff)
{
	if (false == IsValid(BaseBuff) || false == IsValid(OwnerCharacter))
	{
		return;
	}

	AddBuffParticleSystem(BaseBuff);
}

void ABaseBuffActor::RemoveBuffInfo(UBaseBuff* BaseBuff)
{
	if (BuffParticleSystems.Contains(BaseBuff))
	{
		UParticleSystemComponent* ParticleSystemComponent = BuffParticleSystems[BaseBuff];

		if (IsValid(ParticleSystemComponent))
		{
			ParticleSystemComponent->SetTemplate(nullptr);
			ParticleSystemComponent->SetVisibility(false);
			ParticleSystemComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			ParticleSystemComponent->MarkAsGarbage();
			ParticleSystemComponent->DestroyComponent();
		}

		BuffParticleSystems.Remove(BaseBuff);
	}
}

void ABaseBuffActor::AddBuffParticleSystem(UBaseBuff* BaseBuff)
{
	if (true == BaseBuff->IsPassiveBuff() || 0 > BaseBuff->BuffStateIndex())
		return;

	if (UParticleSystemComponent* BuffParticleSystemComp = CreateParticleSystemComponent(BaseBuff))
	{
		bool hideparticle = OwnerCharacter->IsHidden() || !OwnerCharacter->GetMesh()->IsVisible();
		BuffParticleSystemComp->SetVisibility(!hideparticle);
		BuffParticleSystems.Add(BaseBuff, BuffParticleSystemComp);
	}
}

UParticleSystemComponent* ABaseBuffActor::CreateParticleSystemComponent(UBaseBuff* BaseBuff)
{
	int32 BuffParticleIdx = BaseBuff->BuffStateIndex();

	UParticleSystemComponent* BuffParticleSystemComp = NewObject<UParticleSystemComponent>(this);

	if (nullptr != BuffParticleSystemComp)
	{
		BuffParticleSystemComp->bAutoDestroy = false;
		BuffParticleSystemComp->bAllowAnyoneToDestroyMe = true;
		BuffParticleSystemComp->SecondsBeforeInactive = 0.0f;
		BuffParticleSystemComp->bAutoActivate = true;
		BuffParticleSystemComp->bOverrideLODMethod = false;
		BuffParticleSystemComp->SetRelativeLocation(FVector(ForceInit));
		BuffParticleSystemComp->SetRelativeRotation(FRotator::ZeroRotator);
		BuffParticleSystemComp->SetRelativeScale3D(FVector(1.f));
		BuffParticleSystemComp->RegisterComponentWithWorld(this->GetWorld());
		BuffParticleSystemComp->ActivateSystem(true);

		BuffParticleSystemComp->SetTemplate(CreateBuffEffectParticle(BaseBuff));
		BuffParticleSystemComp->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GetParticleAttachBoneName(BuffParticleIdx, BaseBuff->GetAttachedBoneName()));

		//if (BaseBuff->IsA(UCIncreaseAtkAreaBuff::StaticClass()))
		//	BuffParticleSystemComp->SetUsingAbsoluteRotation(false);
	}

	return BuffParticleSystemComp;
}

UParticleSystem* ABaseBuffActor::CreateBuffEffectParticle(UBaseBuff* BaseBuff)
{
	//if (false == IsValid(BuffStateActorPool))
	//	return nullptr;

	FString BuffParticlePath = "";
	EBuffEffectType BuffParticleIdx = static_cast<EBuffEffectType>(BaseBuff->BuffStateIndex());

	switch (BuffParticleIdx)
	{
	case EBuffEffectType::Flame: 
		BuffParticlePath = "/Game/Effect/SimpleEffect/Buff/FX_DeBuff_Fire001_PS.FX_DeBuff_Fire001_PS";
		break;
	default:
		BuffParticlePath = "";
		break;
	}

	UParticleSystem* ParticleSystem = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, *BuffParticlePath));

	return ParticleSystem;
}

FName ABaseBuffActor::GetParticleAttachBoneName(int32 BuffParticleIdx, FName BoneName)
{
	switch (static_cast<EBuffEffectType>(BuffParticleIdx))
	{
	case EBuffEffectType::Flame:
		return "root";
	default: return "";
	}
}

