// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffControllerComponent.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "BaseBuff.h"

#include "BuffList/AttackDamageBuff.h"
#include "BuffList/AttackDamageDebuff.h"
#include "BuffList/FlameDebuff.h"
#include "BuffList/FreezeDeBuff.h"
#include "BuffList/StunDebuff.h"
#include "BuffList/SlowDebuff.h"
#include "BuffList/HealBuff.h"
#include "BuffList/PeriodHealBuff.h"
#include "BuffList/InvincibleBuff.h"
#include "BuffList/ShieldBuff.h"

#include "BuffStateActor.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "BuffStateActor.h"

// Sets default values for this component's properties
UBuffControllerComponent::UBuffControllerComponent() : BuffStateActor(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// spawn buff state actor
	if (nullptr != OwnerCharacter && nullptr == BuffStateActor)
	{
		BuffStateActor = Cast<ABuffStateActor>(SpawnBuffActor(EBuffActorType::eBuffStateActor, nullptr));
	}
}

void UBuffControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// DestroyAllBuff
	UpdateBuffInfoCallBack.Unbind();
	// clear buff state actor
	Super::EndPlay(EndPlayReason);
}

void UBuffControllerComponent::PostLoad()
{
	Super::PostLoad();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}

void UBuffControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickBuff(DeltaTime);
	DeleteBuffCheck();
}

UBaseBuff* UBuffControllerComponent::CreateBuff(ABaseCharacter* Caster, const FHeroBuffInfo& HeroBuffInfo, bool bAllowedDuplicate)
{
	if (Caster == nullptr || OwnerCharacter == nullptr)
		return nullptr;

	if (HeroBuffInfo.BuffType == EHeroBuffType::None_Buff)
		return nullptr;

	if (EBuffTargetType::Team == HeroBuffInfo.BuffTarget)
	{

	}
	else
	{
		UBaseBuff* BaseBuff = FindSameBuff(Caster, HeroBuffInfo);
		if (false == bAllowedDuplicate && nullptr != BaseBuff
			&& false == BaseBuff->IsDuplicated())
		{
			RenewBuff(BaseBuff, HeroBuffInfo);

			return nullptr;
		}

		return CreateBuff_Implementation(Caster, HeroBuffInfo, bAllowedDuplicate);
	}
	return nullptr;
}

void UBuffControllerComponent::DestroyBuff(UBaseBuff* BaseBuff)
{
	if (INDEX_NONE == HeroBuffArray.Find(BaseBuff))
		return;

	DeleteHeroBuffArray.Add(BaseBuff);

	if (nullptr == OwnerCharacter)
		return;
}

UBaseBuff* UBuffControllerComponent::FindSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& HeroPassiveBuff)
{
	for (UBaseBuff* HeroBuff : HeroBuffArray)
	{
		if (true == HeroBuff->IsSameBuff(Caster, HeroPassiveBuff))
			return HeroBuff;
	}

	return nullptr;
}

void UBuffControllerComponent::RenewBuff(UBaseBuff* const BaseBuff, const FHeroBuffInfo& HeroBuffInfo)
{
	if (BaseBuff == nullptr)
		return;
	BaseBuff->RenewBuff(HeroBuffInfo);
}

void UBuffControllerComponent::DeleteBuffCheck()
{
	if (0 >= DeleteHeroBuffArray.Num())
		return;

	for (UBaseBuff* deleteBuff : DeleteHeroBuffArray)
	{
		if (BuffStateActor)
			BuffStateActor->RemoveBuffInfo(deleteBuff);

		HeroBuffArray.Remove(deleteBuff);
		deleteBuff->EndBuff(true);

		deleteBuff = nullptr;
	}

	DeleteHeroBuffArray.Empty();
	UpdateBuffInfo();
}

void UBuffControllerComponent::FindHaveBuff(const UClass* ClassType, TArray<UBaseBuff*>& BuffArray)
{
	if (nullptr == ClassType)
		return;

	BuffArray.Empty();

	for (auto HeroBuff : HeroBuffArray)
	{
		if (true == HeroBuff->IsA(ClassType))
			BuffArray.Add(HeroBuff);
	}
}

void UBuffControllerComponent::ClearBuffStateActor()
{
	if (nullptr != BuffStateActor)
	{
		DestroyBuffStateActor(BuffStateActor);
		BuffStateActor = nullptr;
	}

	//for (auto& AdditionalBuffStateActor : AdditionalBuffStateActorMap)
	//{
	//	ACBaseBuffActor* BaseBuffActor = AdditionalBuffStateActor.Value;
	//	DestroyBuffStateActor(BaseBuffActor);
	//}
	//AdditionalBuffStateActorMap.Empty();
}

void UBuffControllerComponent::ShowBuffEffects()
{
	if (IsValid(BuffStateActor))
		BuffStateActor->ShowBuffStateActor();
}

void UBuffControllerComponent::HideBuffEffects()
{
	if (IsValid(BuffStateActor))
		BuffStateActor->HideBuffStateActor();
}

void UBuffControllerComponent::UpdateBuffInfo()
{
	UpdateBuffInfoCallBack.ExecuteIfBound();
}

void UBuffControllerComponent::TickBuff(float DeltaTime)
{
	if (0 >= HeroBuffArray.Num())
		return;

	float OriginDeltaTime = DeltaTime;

	TArray<UBaseBuff*> TickProcessBuff = HeroBuffArray;
	for (UBaseBuff* HeroBuff : TickProcessBuff)
	{
		HeroBuff->Tick(OriginDeltaTime);
	}
}

bool UBuffControllerComponent::IsNecessaryBuffActor(UBaseBuff* CheckBuff)
{
	if (false == CheckBuff->IsNecessaryBuffActor())
		return false;

	return true;
}

UBaseBuff* UBuffControllerComponent::CreateBuff_Implementation(ABaseCharacter* Caster, const FHeroBuffInfo& HeroBuffInfo, bool bAllowedDuplicate)
{
	UBaseBuff* BaseBuff = CreateInstance(HeroBuffInfo.BuffType, HeroBuffInfo);

	if (nullptr == BaseBuff)
		return nullptr;

	BaseBuff->SetOwnerCharacter(OwnerCharacter);
	BaseBuff->InitBuff(Caster, HeroBuffInfo);
	BaseBuff->SetDuplicated(bAllowedDuplicate);
	BaseBuff->BindCallBackFunc(this, &UBuffControllerComponent::DestroyBuff);

	//switch (HeroBuffInfo.BuffType)
	//{
	//default:
	//	break;
	//}

	// Tao ra 1 actor de hien thi hieu ung (choang, troi chan, ...)
	if (true == IsNecessaryBuffActor(BaseBuff))
	{
		if (EBuffActorType::eBuffStateActor == BaseBuff->GetSpawnActorType())
		{
			if (BuffStateActor)
				BuffStateActor->AddBuffInfo(BaseBuff);
		}
	}
	
	HeroBuffArray.Add(BaseBuff);
	BaseBuff->BeginBuff();
	UpdateBuffInfo();

	return BaseBuff;
}

UBaseBuff* UBuffControllerComponent::CreateInstance(const EHeroBuffType& type, const FHeroBuffInfo& HeroBuffInfo)
{
	switch (type)
	{
	case EHeroBuffType::Damage_Increase:	return	NewObject<UAttackDamageBuff>();
	case EHeroBuffType::Damage_Decrease:	return	NewObject<UAttackDamageDebuff>();
	case EHeroBuffType::Flame:				return	NewObject<UFlameDebuff>();
	case EHeroBuffType::Freezing:			return	NewObject<UFreezeDeBuff>();
	case EHeroBuffType::Stun:				return	NewObject<UStunDebuff>();
	case EHeroBuffType::Slow:				return	NewObject<USlowDebuff>();
	case EHeroBuffType::HP_Recovery:		return	NewObject<UHealBuff>();
	case EHeroBuffType::HP_Recovery_Loop:	return	NewObject<UPeriodHealBuff>();
	case EHeroBuffType::Invincible:			return	NewObject<UInvincibleBuff>();
	case EHeroBuffType::Shield:				return	NewObject<UShieldBuff>();
	default:
		return nullptr;
	}
	return nullptr;
}

ABaseBuffActor* UBuffControllerComponent::SpawnBuffActor(EBuffActorType BuffActorType, UBaseBuff* BaseBuff)
{
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode)
		return nullptr;

	//UBuffStateActorPool* BuffStateActorPool = Cast<UBuffStateActorPool>(GameMode->GetComponentByClass(UBuffStateActorPool::StaticClass()));
	TSubclassOf<ABaseBuffActor> BaseBuffActorBPClass = UAssetMgr::LoadClass("/Game/Blueprints/Battle/Buff/BuffStateActorBP", ABaseBuffActor::StaticClass(), nullptr);
	ABaseBuffActor* BaseBuffActor = GetWorld()->SpawnActor<ABaseBuffActor>(BaseBuffActorBPClass, FTransform::Identity);

	if (nullptr != BaseBuffActor)
	{
		if (ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner()))
			BaseBuffActor->InitBuffStateActor(Owner, BaseBuff);
	}

	return BaseBuffActor;
}

void UBuffControllerComponent::DestroyBuffStateActor(ABaseBuffActor* BaseBuffActor)
{
	if (IsValid(BaseBuffActor))
	{
		BaseBuffActor->EndBuffStateActor();
		BaseBuffActor->Destroy();
	}
}

