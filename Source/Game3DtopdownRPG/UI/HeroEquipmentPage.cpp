// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroEquipmentPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryEquipContainerWidget.h"
#include "UIUnit/InventoryContainerWidget.h"
#include "UIUnit/EquipmentSlotWidget.h"
#include "UIUnit/ItemSlotWidget.h"
#include "UIUnit/TopMenuWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Kismet/GameplayStatics.h"

void UHeroEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	for (int tabIndex = 0; tabIndex < static_cast<int32>(EEquipmentItemTabCategory::Max); ++tabIndex)
	{
		UButton* button = GetOwnUI<UButton>(FString::Printf(TEXT("Button_Tab_%d"), tabIndex));
		UImage* imageforcus = GetOwnUI<UImage>(FString::Printf(TEXT("Image_forcus_%d"), tabIndex));

		if (nullptr != button) TabEquipmentItemButtons.Emplace(button);
		if (nullptr != imageforcus) TabEquipmentItemForcuss.Emplace(imageforcus);
	}

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
			slot->SetTapEventEx(this);
			EquipmentSlots.Emplace(slot);
		}
	}

	for (int tabIndex = 5; tabIndex < static_cast<int32>(EItemTabCategory::Max) + 5; ++tabIndex)
	{
		UButton* button = GetOwnUI<UButton>(FString::Printf(TEXT("Button_Tab_%d"), tabIndex));
		UImage* imageforcus = GetOwnUI<UImage>(FString::Printf(TEXT("Image_forcus_%d"), tabIndex));

		if (nullptr != button) TabItemButtons.Emplace(button);
		if (nullptr != imageforcus) TabItemForcuss.Emplace(imageforcus);
	}

	for (int indexSlot = 0; indexSlot < 3; ++indexSlot)
	{
		UItemSlotWidget* slot = GetOwnUI<UItemSlotWidget>(FString::Printf(TEXT("ItemSlotWidgetBP_%d"), indexSlot));
		if (nullptr != slot)
		{
			slot->InitUnit(GameMode);
			slot->SetDropEventEx(this);
			slot->SetTapEventEx(this);
			ItemSlots.Emplace(slot);
		}
	}

	ItemContainer_Scroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidge_ItemContainer"));
	if (nullptr != ItemContainer_Scroll)
	{
		ItemContainer_Scroll->InitUnit(GameMode);
		ItemContainer_Scroll->ChildUpdateEvent.BindUObject(this, &UHeroEquipmentPage::UpdateChildItem);
	}

	VerticalBoxItemEquipment = GetOwnUI<UVerticalBox>(TEXT("VerticalBox_EquipItem"));
	VerticalBoxItem = GetOwnUI<UVerticalBox>(TEXT("VerticalBox_Item"));

	for (int indexParam = 0; indexParam < static_cast<int32>(ECharacterParam::Max); ++indexParam)
	{
		UTextBlock* textparam = GetOwnUI<UTextBlock>(FString::Printf(TEXT("TextParam_%d"), indexParam));
		if (nullptr != textparam)
		{
			HeroParam.Emplace(textparam);
		}
	}

	TopMenu = GetOwnUI<UTopMenuWidget>(TEXT("TopMenuWidgetBP"));
	if (TopMenu != nullptr)
	{
		TopMenu->InitUnit(GameMode);
	}

	OnTapTabEquipmentItemCategory(EEquipmentItemTabCategory::All);
	OnTapTabItemCategory(EItemTabCategory::All);
}

void UHeroEquipmentPage::Update()
{
	Super::Update();

	m_CurrentItemEquipmentArray.Empty();

	switch (m_CurrentEquipmentItemCategory)
	{
	case EEquipmentItemTabCategory::All:
		m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentInBackpackArray();
		break;
	case EEquipmentItemTabCategory::Weapon:
		m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Weapon, EInventoryLocation::InBackpack);
		break;
	case EEquipmentItemTabCategory::Shield:
		m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Shield, EInventoryLocation::InBackpack);
		break;
	case EEquipmentItemTabCategory::Shoe:
		m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Shoe, EInventoryLocation::InBackpack);
		break;
	case EEquipmentItemTabCategory::Belt:
		m_CurrentItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Belt, EInventoryLocation::InBackpack);
		break;
	case EEquipmentItemTabCategory::Max:
		break;
	default:
		break;
	}

	m_CurrentItemArray.Empty();

	switch (m_CurrentItemCategory)
	{
	case EItemTabCategory::All:
		m_CurrentItemArray = GetMgr(UItemMgr)->GetItemInBackpackArray();
		break;
	case EItemTabCategory::Common:
		m_CurrentItemArray = GetMgr(UItemMgr)->GetItemArrayByCategory(EItemCategory::Common, EInventoryLocation::InBackpack);
		break;
	case EItemTabCategory::Material:
		m_CurrentItemArray = GetMgr(UItemMgr)->GetItemArrayByCategory(EItemCategory::Material, EInventoryLocation::InBackpack);
		break;
	case EItemTabCategory::Potion:
		m_CurrentItemArray = GetMgr(UItemMgr)->GetItemArrayByCategory(EItemCategory::Potion, EInventoryLocation::InBackpack);
		break;
	case EItemTabCategory::Max:
		break;
	default:
		break;
	}
	
	if (nullptr != ItemContainer_Scroll) ItemContainer_Scroll->SetChildCount(m_CurrentItemArray.Num());
	if (nullptr != ItemEquipmentContainer_SCroll) ItemEquipmentContainer_SCroll->SetChildCount(m_CurrentItemEquipmentArray.Num());

	UpdateEquipmentSlots();
	UpdateNormalEquipmentSlots();
	UpdateHeroParams();
	if(nullptr != TopMenu) TopMenu->Update();
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
			basecharacter->EquipItem(Container->GetInventoryEquipment()->GetGameItemInfo(), false);
		}
	}

	Update();
}

void UHeroEquipmentPage::OnTapEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container)
{
	VerticalBoxItemEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	VerticalBoxItem->SetVisibility(ESlateVisibility::Collapsed);
}

void UHeroEquipmentPage::OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container)
{
	FItemEquipmentInfoRecord* infoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(container->GetGameItemInfo().m_ItemRecKey)));
	if (infoRecord == nullptr) return;
	UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString::Printf(TEXT("Change %s to inventory success"), *infoRecord->DesName));
	GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(container->GetGameItemInfo(), EInventoryLocation::InInventory);

	Update();
}

void UHeroEquipmentPage::OnDropItemSlot(int32 rec_key, UItemSlotWidget* Container)
{
	if (nullptr == Container) return;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		ABaseCharacter* basecharacter = Cast<ABaseCharacter>(PlayerCharacter);
		if (basecharacter)
		{
			basecharacter->EquipNormalItem(Container->GetInventoryContainer()->GetGameItemInfo(), Container->EquipPosition, false);
		}
	}

	Update();
}

void UHeroEquipmentPage::OnTapItemSlot(int32 rec_key, UItemSlotWidget* Container)
{
	VerticalBoxItemEquipment->SetVisibility(ESlateVisibility::Collapsed);
	VerticalBoxItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UHeroEquipmentPage::SetHeroCharacter(ABaseCharacter* herocharacter)
{
	if (nullptr == herocharacter) return;
	character = herocharacter;
	for (UEquipmentSlotWidget* slot : EquipmentSlots)
	{
		slot->SetHeroCharacter(character);
	}

	for (UItemSlotWidget* slot: ItemSlots)
	{
		slot->SetHeroCharacter(character);
	}
}

void UHeroEquipmentPage::OnTapTabEquipmentItemCategory(EEquipmentItemTabCategory tab)
{
	if (tab == EEquipmentItemTabCategory::Max) return;
	m_CurrentEquipmentItemCategory = tab;

	// hide all tab forcus
	for (int indextab = 0; indextab < TabEquipmentItemForcuss.Num(); ++indextab)
	{
		TabEquipmentItemForcuss[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabEquipmentItemForcuss[static_cast<int32>(tab)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Update();
}

void UHeroEquipmentPage::OnTapTabItemCategory(EItemTabCategory tab)
{
	if (tab == EItemTabCategory::Max) return;
	m_CurrentItemCategory = tab;

	// hide all tab forcus
	for (int indextab = 0; indextab < TabItemForcuss.Num(); ++indextab)
	{
		TabItemForcuss[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabItemForcuss[static_cast<int32>(tab)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Update();
}

void UHeroEquipmentPage::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_CurrentItemArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	//InventoryContainer->SetButtonEventEx(this);
}

void UHeroEquipmentPage::UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemEquipmentArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_CurrentItemEquipmentArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	//InventoryContainer->SetButtonEventEx(this);

	InventoryContainer->SetCtrlButtonEventEx(this);
}

void UHeroEquipmentPage::UpdateEquipmentSlots()
{
	for (UEquipmentSlotWidget* slot : EquipmentSlots)
	{
		slot->Update();
	}
}

void UHeroEquipmentPage::UpdateNormalEquipmentSlots()
{
	for (UItemSlotWidget* slot : ItemSlots)
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
		float paramvalue = 0.f;
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

