// Fill out your copyright notice in the Description page of Project Settings.


#include "StageNaviButton.h"
#include "Game3DtopdownRPG/DataTable/StageTable.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"

void UStageNaviButton::CacheOwnUI()
{
	Super::CacheOwnUI();

	imageStage = GetOwnUI<UImage>(TEXT("Image_Stage"));
	switcherSelect = GetOwnUI<UWidgetSwitcher>(TEXT("WidgetSwitcher"));
}

void UStageNaviButton::NativeConstruct()
{
	Super::NativeConstruct();

	CacheOwnUI();
}

void UStageNaviButton::SetInfo(int32 ChapterReckey, bool isfirst /*= false*/, bool islast /*= false*/)
{
	this->m_ChapterReckey = ChapterReckey;

	FString PathFrame = "";
	if (isfirst)
	{
		PathFrame = "/Game/UI/Sprites/Components/Button/Stage_Start.Stage_Start";	
	}
	else if (islast)
	{
		PathFrame = "/Game/UI/Sprites/Components/Button/Stage_End.Stage_End";
	}
	else
	{
		PathFrame = "/Game/UI/Sprites/Components/Button/Stage_Middle.Stage_Middle";
	}

	UTexture2D* TexFrame = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathFrame);

	imageStage->SetBrushFromTexture(TexFrame);
}

void UStageNaviButton::OnTapButton()
{
	OwnerTap_DelegateEx.ExecuteIfBound(m_ChapterReckey, this);
}

void UStageNaviButton::SetSelect(bool bSelect)
{
	if (bSelect)
		switcherSelect->SetActiveWidgetIndex(1);
	else
		switcherSelect->SetActiveWidgetIndex(0);
}
