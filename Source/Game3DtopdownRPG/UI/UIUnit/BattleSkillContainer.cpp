// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSkillContainer.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/HeroMgr.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"

bool UBattleSkillContainer::Initialize()
{
	bool isInitialize = Super::Initialize();
	if (isInitialize)
	{

	}

	return isInitialize;
}

void UBattleSkillContainer::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBarCooldown = GetOwnUI<UProgressBar>(TEXT("ProgressBar_Cooldown"));
	TextNumberCooldown = GetOwnUI<UTextBlock>(TEXT("TextBlock_Number"));
	imageSkillIcon = GetOwnUI<UImage>(TEXT("Image_icon"));
}

void UBattleSkillContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn) return;

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Pawn);
	if (!BaseCharacter) return;

	FNativeSkillInfo skillinfo = BaseCharacter->GetNativeSkillInfo(SkillIndex);

	float GameTimeInSeconds = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	float time = skillinfo.CoolDownTime - GameTimeInSeconds;

	if (skillinfo.state != EBattleSkillState::Max)
	{
		switch (skillinfo.state)
		{
		case EBattleSkillState::Available:
			ProgressBarCooldown->SetPercent(0);
			TextNumberCooldown->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EBattleSkillState::Using:
			ProgressBarCooldown->SetPercent(100);
			break;
		case EBattleSkillState::Cooldown:
			if (time >= 0.0f)
			{
				ProgressBarCooldown->SetPercent(time*1.0f/skillinfo.CoolDownDuration);
				TextNumberCooldown->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				TextNumberCooldown->SetText(FText::AsNumber((int)time));
			}
			break;
		default:
			break;
		}
	}
}

void UBattleSkillContainer::SetSkillInfo(EHeroClass heroclass)
{
	FSkillInfoRecord* record = GetMgr(UHeroMgr)->GetSkillInfoRecord(heroclass, SkillIndex);
	if (nullptr == record) return;
	if (nullptr == imageSkillIcon) return;

	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(record->SkillImage, EGameTextureType::Skill);

	if (nullptr == Tex)
		return;

	imageSkillIcon->SetBrushFromTexture(Tex);
}
