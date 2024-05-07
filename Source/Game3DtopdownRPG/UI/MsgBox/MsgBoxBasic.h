// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBaseMsgBox.h"
#include "Game3DtopdownRPG/Define/MsgStruct.h"
#include "MsgBoxBasic.generated.h"

class UUIBaseButton;

DECLARE_DELEGATE(FCallMsgFuncOnTap);

UCLASS()
class GAME3DTOPDOWNRPG_API UMsgBoxBasic : public UUIBaseMsgBox
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	virtual void Destroy(class UUIBaseMgr* InUIManager) override;

	template<class T>
	void AddHandler(EMsgEventButtonType buttonType, T* Owner, const FName& FuntionName)
	{
		if (buttonType == EMsgEventButtonType::Left) {
			HandlerLeft.Unbind();
			HandlerLeft.BindUFunction(Owner, FuntionName);
		}
	}

	UFUNCTION(BlueprintCallable)
	virtual void OnTap();

protected:
	FCallMsgFuncOnTap HandlerLeft;

	UUIBaseButton* button;
};
