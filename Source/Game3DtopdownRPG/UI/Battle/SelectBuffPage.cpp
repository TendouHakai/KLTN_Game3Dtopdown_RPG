// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectBuffPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/SelectBuffWidget.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffStruct.h"

void USelectBuffPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	for (int index = 0; index < 3; ++index)
	{
		USelectBuffWidget* widget = GetOwnUI<USelectBuffWidget>(FString::Printf(TEXT("SelectBuffWidget_%d"), index));
		if (widget != nullptr)
		{
			widget->InitUnit(GameMode);
			widget->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnSelectBuff")));
			selectbuffs.Emplace(widget);
		}
	}
}

void USelectBuffPage::NativeConstruct()
{
	Super::NativeConstruct();
}

void USelectBuffPage::SetCaster(ABaseCharacter* Caster)
{
	if (Caster == nullptr) return;
	this->caster = Caster;

	for (USelectBuffWidget* widget : selectbuffs)
	{
		widget->SetCharacter(Caster);
	}
}

void USelectBuffPage::SetBuffInfos(TArray<FHeroBuffInfo> buffinfos)
{
	int num = buffinfos.Num() < 3 ? buffinfos.Num() : 3;
	for (int index = 0; index < num; ++index)
	{
		selectbuffs[index]->SetInfo(buffinfos[index]);
	}
}

void USelectBuffPage::OnSelectBuff()
{
	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}
