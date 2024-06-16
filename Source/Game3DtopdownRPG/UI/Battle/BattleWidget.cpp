// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/ItemSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffControllerComponent.h"
#include "Game3DtopdownRPG/Battle/Buff/BaseBuff.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/FlameDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/FreezeDeBuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/BleedingDeBuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/BlindnessDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/AttackDamageDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/SlowDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/StunDebuff.h"

void UBattleWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	for (int slotIndex = 0; slotIndex < 3; ++slotIndex)
	{
		UItemSlotWidget* slot = GetOwnUI<UItemSlotWidget>(FString::Printf(TEXT("ItemSlotWidgetBP_%d"), slotIndex));
		if (nullptr != slot)
		{
			slots.Emplace(slot);
			if (character != nullptr) slot->SetHeroCharacter(character);
			slot->SetTapEventEx(this);
		}
	}
}

void UBattleWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBattleWidget::Update()
{
	Super::Update();

	UpdateNormalEquipmentSlots();

}

void UBattleWidget::SetHeroCharacter(ABaseCharacter* hero)
{
	if (nullptr == hero) return;
	character = hero;
	for (UItemSlotWidget* slot : slots)
	{
		slot->SetHeroCharacter(hero);
	}

	Update();
}

void UBattleWidget::OnTapItemSlot(int32 rec_key, UItemSlotWidget* Container)
{
	if (nullptr == Container) return;
	if (nullptr == character) return;

	FHeroInfo heroinfo = character->GetHeroInfo();

	FGameItemInfo gameinfo = heroinfo.m_EquipNormal[Container->EquipPosition];
	if (gameinfo.m_ItemRecKey == 0) return;

	FItemInfoRecord* iteminfo = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
	if (nullptr == iteminfo)
		return;
	if (iteminfo->CanUse == false) return;

	if (iteminfo->ItemType == EItemType::Potion)
	{
		FItemBuffRecord* record = GetMgr(UItemMgr)->GetItemBufInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
		if (record == nullptr) return;

		//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//if (PlayerCharacter == nullptr) return;
		//ABaseCharacter* character = Cast<ABaseCharacter>(PlayerCharacter);
		if (character == nullptr) return;

		if (record->IsBuff)
		{
			character->HeroBuffController->CreateBuff(character, record->buffinfo);
		}
		else
		{
			TArray<UBaseBuff*> buffs;
			switch (record->buffinfo.BuffType)
			{
			case EHeroBuffType::Flame:				character->FindHaveBuff(UFlameDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Freezing:			character->FindHaveBuff(UFreezeDeBuff::StaticClass(), buffs); break;
			case EHeroBuffType::Bleeding:			character->FindHaveBuff(UBleedingDeBuff::StaticClass(), buffs); break;
			case EHeroBuffType::Blindness:			character->FindHaveBuff(UBlindnessDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Damage_Decrease:	character->FindHaveBuff(UAttackDamageDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Slow:				character->FindHaveBuff(USlowDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Stun:				character->FindHaveBuff(UStunDebuff::StaticClass(), buffs); break;
			default:
				break;
			}

			for (UBaseBuff* buff : buffs)
			{
				buff->EndBuff();
			}
		}
		FString str = FString::Printf(TEXT("Used %s"), *iteminfo->DesName);
	}

	character->UseEquipNormalItem(Container->EquipPosition);

	Update();
}

void UBattleWidget::OnTapItemEquipSlot(int32 index)
{
	if (slots.IsValidIndex(index) == false) return;

	slots[index]->OnTapEvent();
}

void UBattleWidget::UpdateNormalEquipmentSlots()
{
	for (UItemSlotWidget* slot : slots)
	{
		slot->Update();
	}
}

void UBattleWidget::UpdateSkillSlot()
{

}
