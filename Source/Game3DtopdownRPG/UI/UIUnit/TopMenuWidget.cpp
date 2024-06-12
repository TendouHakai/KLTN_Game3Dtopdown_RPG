// Fill out your copyright notice in the Description page of Project Settings.


#include "TopMenuWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Util/CppFunctionLibrary.h"

void UTopMenuWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	textEnergy = GetOwnUI<UTextBlock>(TEXT("TextBlock_Energy"));
	textGold = GetOwnUI<UTextBlock>(TEXT("TextBlock_Gold"));
	textRemainTime = GetOwnUI<UTextBlock>(TEXT("TextBlock_EnergyRemainTime"));
}

void UTopMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTopMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetMgr(UItemMgr)->GetMaxEnergy() <= GetMgr(UItemMgr)->GetEnergy())
	{
		textRemainTime->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	float remainTime = GetMgr(UItemMgr)->GetEnergyRemainTime() - (FDateTime::Now().GetTimeOfDay().GetTotalSeconds() - GetMgr(UItemMgr)->GetEnergyResetTime());
	if (remainTime >= 0)
	{
		textRemainTime->SetText(UCppFunctionLibrary::ToMinutsText_NoGap((int32)remainTime));
		textRemainTime->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		GetMgr(UItemMgr)->AddEnergy(1, true);
		Update();
	}
}

void UTopMenuWidget::Update()
{
	Super::Update();

	textEnergy->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), GetMgr(UItemMgr)->GetEnergy(), GetMgr(UItemMgr)->GetMaxEnergy())));
	textGold->SetText(FText::AsNumber(GetMgr(UItemMgr)->GetGold()));
}
