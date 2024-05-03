// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffStateComponent.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "MovieScene.h"
#include "Game3DtopdownRPG/Battle/Buff/BaseBuff.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/HeroBuffMgr.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffStruct.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Blueprint/SlateBlueprintLibrary.h"

UBuffStateComponent::UBuffStateComponent() : bShowBuffWidget(false)
{
}

void UBuffStateComponent::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{ 
	Super::NativeTick(MyGeometry, InDeltaTime);

	USlateBlueprintLibrary::LocalToViewport(GetWorld(), MyGeometry, FVector2D::ZeroVector, PixelPosition, ViewPortPosition);
	//ViewPortPosition = USlateBlueprintLibrary::LocalToAbsolute(MyGeometry, FVector2D::ZeroVector);
}

void UBuffStateComponent::CacheOwnUI()
{
	Super::CacheOwnUI();

	BuffTime = GetOwnUI<UTextBlock>(TEXT("TextBlock_bufftime"));
	BuffIcon = GetOwnUI<UImage>(TEXT("Image_buff"));
	BuffStateAnim = GetWidgetAnimation(TEXT("Ani_Buff"));
}

void UBuffStateComponent::Destroy(UUIBaseMgr* InUIManager)
{
	if (OnSelectCallBack.IsBound())
		OnSelectCallBack.Unbind();

	Super::Destroy(InUIManager);
}

bool UBuffStateComponent::SetInfo(UBaseBuff* BaseBuff)
{
	UpdateBuffTimeInfo(BaseBuff);

	// class buff hero manager
 	FBuffInfoRecord* BuffInfoRecord = GetMgr(UHeroBuffMgr)->GetHeroBuffInfoRecord((int32)BaseBuff->HeroBuffInfo.BuffType, BaseBuff->HeroBuffInfo.BuffCondition);

	if (BuffInfoRecord == nullptr) return false;
	ShowComponent(true);

	BuffInfoText = BaseBuff->GetBuffTextInfo();
	SetBuffIcon(BuffInfoRecord->BuffIcon);

	return true;
}

void UBuffStateComponent::SetInfo(const FHeroBuffInfo& HeroBuffInfo)
{

}

void UBuffStateComponent::UpdateBuffTimeInfo(UBaseBuff* BaseBuff)
{
	if (nullptr != BuffTime)
	{
		if (true == BaseBuff->bIsPassiveBuff)
		{
			BuffTime->SetText(FText::GetEmpty());
		}
		else
		{
			int32 RemainSecsAsInt = BaseBuff->GetRemainTime();

			if (IsTimeShowException(BaseBuff))
				BuffTime->SetText(FText::GetEmpty());
			else
				BuffTime->SetText(FText::AsNumber(RemainSecsAsInt));
			if (IsBlinkException(BaseBuff))
				return;

			const int32 BlinkAnimStartAt = 3;
			if (RemainSecsAsInt <= BlinkAnimStartAt)
			{
				if (false == IsPlayingAnimation())
				{
					PlayAnimation(BuffStateAnim, 0.0f, 0);
				}
			}
			else
			{
				if (true == IsPlayingAnimation())
				{
					InitIconOpacity();
					StopAnimation(BuffStateAnim);
				}
			}
		}
	}
}

void UBuffStateComponent::UpdateInterruptInfo(UBaseBuff* BaseBuff)
{
}

void UBuffStateComponent::ShowComponent(bool bShow)
{
	if (bShow == IsVisible())
		return;

	if (false == bShow)
	{
		StopAnimation(BuffStateAnim);
		SetVisibility(ESlateVisibility::Collapsed);

		if (bShowBuffWidget)
		{
			bShowBuffWidget = false;
		}
	}
	else
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBuffStateComponent::OnTapBuffIcon(bool bshow)
{
	OnSelectCallBack.ExecuteIfBound(this, bshow);
}

bool UBuffStateComponent::IsTimeShowException(UBaseBuff* BaseBuff)
{
	return false;
}

bool UBuffStateComponent::IsBlinkException(UBaseBuff* BaseBuff)
{
	return false;
}

void UBuffStateComponent::SetBuffIcon(FString name)
{
	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(name, EGameTextureType::Buff);

	if (nullptr == BuffIcon || nullptr == Tex)
		return;

	BuffIcon->SetBrushFromTexture(Tex);
}
