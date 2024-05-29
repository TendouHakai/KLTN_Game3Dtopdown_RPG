// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroEquipmentPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryEquipContainerWidget.h"
#include "UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Kismet/GameplayStatics.h"

void UHeroEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();


	ItemEquipmentContainer_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidge_EquipmentContainer"));
	if (nullptr != ItemEquipmentContainer_SCroll)
	{
		ItemEquipmentContainer_SCroll->InitUnit(GameMode);
		ItemEquipmentContainer_SCroll->ChildUpdateEvent.BindUObject(this, &UHeroEquipmentPage::UpdateChildItemEquipment);
	}

	for (int indexSlot = 0; indexSlot < static_cast<int32>(EItemEquipPosition::Max); ++indexSlot)
	{
		UEquipmentSlotWidget* slot = GetOwnUI<UEquipmentSlotWidget>(FString::Printf(TEXT("EquipmentSlotWidget_%d"), indexSlot));
		if (nullptr != slot)
		{
			slot->InitUnit(GameMode);
			slot->SetDropEventEx(this);
			EquipmentSlots.Emplace(slot);
		}
	}

	for (int indexParam = 0; indexParam < static_cast<int32>(ECharacterParam::Max); ++indexParam)
	{
		UTextBlock* textparam = GetOwnUI<UTextBlock>(FString::Printf(TEXT("TextParam_%d"), indexParam));
		if (nullptr != textparam)
		{
			HeroParam.Emplace(textparam);
		}
	}
}

void UHeroEquipmentPage::Update()
{
	Super::Update();

	m_CurrentItemEquipmentArray.Empty();

	m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentInBackpackArray();

	if (nullptr != ItemEquipmentContainer_SCroll) ItemEquipmentContainer_SCroll->SetChildCount(m_CurrentItemEquipmentArray.Num());

	UpdateEquipmentSlots();
	UpdateHeroParams();
}

void UHeroEquipmentPage::OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container)
{
	if (nullptr == Container) return;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		ABaseCharacter* basecharacter = Cast<ABaseCharacter>(PlayerCharacter);
		if (basecharacter)
		{
			basecharacter->EquipItem(Container->GetInventoryEquipment()->GetGameItemInfo());
		}
	}
}

void UHeroEquipmentPage::SetHeroCharacter(ABaseCharacter* herocharacter)
{
	if (nullptr == herocharacter) return;
	character = herocharacter;
	for (UEquipmentSlotWidget* slot : EquipmentSlots)
	{
		slot->SetHeroCharacter(character);
	}
}

void UHeroEquipmentPage::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{

}

void UHeroEquipmentPage::UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemEquipmentArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_CurrentItemEquipmentArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);
}

void UHeroEquipmentPage::UpdateEquipmentSlots()
{
	for (UEquipmentSlotWidget* slot : EquipmentSlots)
	{
		slot->Update();
	}
}

void UHeroEquipmentPage::UpdateHeroParams()
{
	if (nullptr == character) return;
	FHeroInfo heroinfo = character->GetHeroInfo();
	
	for (int index = 0; index < static_cast<int32>(ECharacterParam::Max); ++index)
	{
		float paramvalue;
		switch ((ECharacterParam)index)
		{
		case ECharacterParam::AttackSpeed:
			paramvalue = heroinfo.m_Param.AttackSpeedRate;
			break;
		case ECharacterParam::CriticalRatio:
			paramvalue = heroinfo.m_Param.CriticalRatio;
		case ECharacterParam::DebuffResistanceRatio:
			paramvalue = heroinfo.m_Param.DebuffResistanceRatio;
			break;
		case ECharacterParam::Def:
			paramvalue = heroinfo.m_Param.Def;
			break;
		case ECharacterParam::HealHP:
			paramvalue = heroinfo.m_Param.HealHP;
			break;
		case ECharacterParam::HP:
			paramvalue = heroinfo.m_Param.HP;
			break;
		case ECharacterParam::MagicDamage:
			paramvalue = heroinfo.m_Param.MagicDamage;
			break;
		case ECharacterParam::MagicDef:
			paramvalue = heroinfo.m_Param.MagicDef;
			break;
		case ECharacterParam::MovementSpeed:
			paramvalue = heroinfo.m_Param.MovementSpeedRate;
			break;
		case ECharacterParam::PhysicDamage:
			paramvalue = heroinfo.m_Param.PhysicDamage;
			break;
		case ECharacterParam::PierceDef:
			paramvalue = heroinfo.m_Param.PierceDef;
			break;
		case ECharacterParam::PiercingMagicDef:
			paramvalue = heroinfo.m_Param.PierceMagicDef;
			break;
		case ECharacterParam::ReduceCoolDownRatio:
			paramvalue = heroinfo.m_Param.ReduceCoolDownRatio;
			break;
		default:
			break;
		}

		if (HeroParam.IsValidIndex(index))
		{
			HeroParam[index]->SetText(FText::AsNumber(paramvalue));
		}
	}
}

