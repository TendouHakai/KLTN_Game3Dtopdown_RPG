// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MsgBoxBasic.h"
#include "Components/SizeBox.h"
#include "MsgBoxReward.generated.h"

class UScrollWidget;
struct FGameItemInfo;
struct FGameItemEquipmentInfo;

DECLARE_DELEGATE(FCallMsgFuncOnTap);

UCLASS()
class GAME3DTOPDOWNRPG_API UMsgBoxReward : public UMsgBoxBasic
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetInfo(TArray<FGameItemInfo>& gameinfos);
	void SetInfo(TArray<FGameItemEquipmentInfo>& gameinfos);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx);

protected:
	USizeBox* sizebox_ScrollItemWidget;
	USizeBox* sizebox_ScrollItemEquipWidget;

	UScrollWidget* ScrollItemWidget;
	UScrollWidget* ScrollItemEquipWidget;
	TArray<FGameItemInfo> items;
	TArray<FGameItemEquipmentInfo> itemEquips;
};
