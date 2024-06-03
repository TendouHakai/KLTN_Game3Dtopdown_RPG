// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MsgBoxBasic.h"
#include "MsgBoxReward.generated.h"

class UScrollWidget;
struct FGameItemInfo;

DECLARE_DELEGATE(FCallMsgFuncOnTap);

UCLASS()
class GAME3DTOPDOWNRPG_API UMsgBoxReward : public UMsgBoxBasic
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetInfo(TArray<FGameItemInfo>& gameinfos);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);

protected:
	UScrollWidget* ScrollWidget;
	TArray<FGameItemInfo> items;
};
