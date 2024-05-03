// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBuffInfo.h"
#include "Components/TextBlock.h"
#include "BuffStateComponent.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UBattleBuffInfo::Init(ABaseGameMode* InGameMode)
{
	Super::Init(InGameMode);
}

void UBattleBuffInfo::NativeConstruct()
{
	Super::NativeConstruct();

	bufftextinfo = GetOwnUI<UTextBlock>(TEXT("TextBuffInfo"));
	AnimHide = GetWidgetAnimation(TEXT("Hide_Ani"));
}

void UBattleBuffInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D PixelPosition;
	FVector2D ViewPortPosition;

	USlateBlueprintLibrary::LocalToViewport(GetWorld(), MyGeometry, FVector2D::ZeroVector, PixelPosition, ViewPortPosition);
}

void UBattleBuffInfo::Destroy(UUIBaseMgr* InUIManager)
{
	Super::Destroy(InUIManager);
}

void UBattleBuffInfo::ShowBuffInfo(UBuffStateComponent* BuffStateComponent, bool bShow)
{
	if(HideTimer.IsValid())
		GetRPGGameInstance()->GetWorld()->GetTimerManager().ClearTimer(HideTimer);
	
	//if (false == bShow || nullptr == BuffStateComponent)
	//{
	//	PlayAnimation(AnimHide);
	//	GetRPGGameInstance()->GetWorld()->GetTimerManager().SetTimer(HideTimer, this, &UBattleBuffInfo::HideBuffInfo, 1.0f);
	//	return;
	//}
	position = BuffStateComponent->GetViewPortPosition();

	SetPositionInViewport(position);

	bufftextinfo->SetText(FText::FromString(BuffStateComponent->GetBuffTextInfo()));

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBattleBuffInfo::HideBuffInfo()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
