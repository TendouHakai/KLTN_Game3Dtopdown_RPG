// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/ItemSlotWidget.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

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

void UBattleWidget::UpdateNormalEquipmentSlots()
{
	for (UItemSlotWidget* slot : slots)
	{
		slot->Update();
	}
}
