// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpProgressBar.h"
#include "Game3DtopdownRPG/Define/HeroStruct.h"
#include "Game3DtopdownRPG/Util/Managers/TableMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"

void UExpProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	progressbar = GetOwnUI<UProgressBar>(TEXT("ProgressBarExp"));
	textLevel = GetOwnUI<UTextBlock>(TEXT("TextBlock_Exp"));
}

void UExpProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bValidWidget) return;
	if (!bStartAddExp) return;

	Exp += addExp * InDeltaTime;

	if (Exp >= endExp)
	{
		Level += 1;
		UpdateInfo();
		// chay effect up level
	}

	progressbar->SetPercent(GetRatioProgressBar(Exp));
	textLevel->SetText(FText::AsNumber(Level));

	if (Exp >= curExp) 
	{
		bStartAddExp = false;
		progressbar->SetPercent(GetRatioProgressBar(curExp));
		textLevel->SetText(FText::AsNumber(Level));
	}
}

void UExpProgressBar::SetHeroExpInfo(FHeroInfo HeroInfo)
{
	Exp = HeroInfo.HeroExp.m_Exp;
	curExp = Exp;
	Level = HeroInfo.m_Level;

	UpdateInfo();
}

void UExpProgressBar::SetAddExp(int32 AddExp)
{
	bStartAddExp = true;
	this->addExp = AddExp;
	this->curExp += AddExp;

	UE_LOG(LogTemp, Warning, TEXT("AddExp"));
}

void UExpProgressBar::SetLevel(int32 level)
{
	curLevel = level;
}

float UExpProgressBar::GetRatioProgressBar(float cExp)
{
	float Ratio = 0.f;
	if (cExp == endExp) 
		Ratio = 1.f;
	else 
		Ratio = (cExp - startExp)*1.0f / (endExp - cExp);
	Ratio = FMath::Clamp(Ratio, 0.f, 1.f);

	return Ratio;
}

void UExpProgressBar::UpdateInfo()
{
	UDataTable* HeroLevelTable = GetMgr(UTableMgr)->HeroLevTable;

	FHeroLevelRecord* heroLevelRecord = HeroLevelTable->FindRow<FHeroLevelRecord>(FName(FString::FromInt(Level)), FString(""));

	if (nullptr == heroLevelRecord) return;

	startExp = heroLevelRecord->SumExp;
	endExp = heroLevelRecord->NextExp;

	progressbar->SetPercent(GetRatioProgressBar(Exp));
	textLevel->SetText(FText::AsNumber(Level));
}
