// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "HeroEquipmentPage.generated.h"

struct FGameItemInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UHeroEquipmentPage : public UUIWidget
{
	GENERATED_BODY()

protected:
	TArray<FGameItemInfo> m_CurrentItem;
};
