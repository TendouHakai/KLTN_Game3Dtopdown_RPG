// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffControllerComponent.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "BaseBuff.h"

// Sets default values for this component's properties
UBuffControllerComponent::UBuffControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuffControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// spawn buff state actor
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
	
	HeroBuffArray.Add(BaseBuff);
	BaseBuff->BeginBuff();
	UpdateBuffInfo();

	return BaseBuff;
}

UBaseBuff* UBuffControllerComponent::CreateInstance(const EHeroBuffType& type, const FHeroBuffInfo& HeroBuffInfo)
{
	switch (type)
	{
	case EHeroBuffType::Damage_Increase: return nullptr;
	default:
		return nullptr;
	}
	return nullptr;
}

