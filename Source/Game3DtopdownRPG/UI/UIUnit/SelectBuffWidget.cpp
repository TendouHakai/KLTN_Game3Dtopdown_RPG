// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectBuffWidget.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/HeroBuffMgr.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/Util/CppFunctionLibrary.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffControllerComponent.h"
#include "Kismet/GameplayStatics.h"

void USelectBuffWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	textNameBuff = GetOwnUI<UTextBlock>(TEXT("TextBlock_NameBuff"));
	imageBuff = GetOwnUI<UImage>(TEXT("Image_Buff"));
	richtextDecrip = GetOwnUI<URichTextBlock>(TEXT("RichTextBlock_decription"));
	textDuration = GetOwnUI<UTextBlock>(TEXT("TextBlock_Duration"));
}

void USelectBuffWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USelectBuffWidget::OnTapSelect()
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (MyCharacter != nullptr)
	{
		(Cast<ABaseCharacter>(MyCharacter))->HeroBuffController->CreateBuff(caster, infoBuff, false);
	}

	OnClicked_Delegate.ExecuteIfBound();
}

void USelectBuffWidget::SetInfo(FHeroBuffInfo buffinfo)
{
	if (buffinfo.BuffType == EHeroBuffType::None_Buff) return;
	infoBuff = buffinfo;

	FBuffInfoRecord* BuffInfoRecord = GetMgr(UHeroBuffMgr)->GetHeroBuffInfoRecord((int32)buffinfo.BuffType, buffinfo.BuffCondition);
	if (BuffInfoRecord == nullptr) return;

	textNameBuff->SetText(FText::FromString(BuffInfoRecord->BuffName));
	richtextDecrip->SetText(UCppFunctionLibrary::GetBuffInfoText(buffinfo));
	textDuration->SetText(FText::AsNumber(buffinfo.Duration));

	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(BuffInfoRecord->BuffIcon, EGameTextureType::Buff);

	if (nullptr == Tex || imageBuff == nullptr)
		return;

	imageBuff->SetBrushFromTexture(Tex);
}

void USelectBuffWidget::SetCharacter(ABaseCharacter* Caster)
{
	if (Caster == nullptr) return;
	this->caster = Caster;
}
