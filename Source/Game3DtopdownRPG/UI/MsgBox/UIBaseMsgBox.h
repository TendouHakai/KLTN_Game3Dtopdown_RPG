// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/RichTextBlock.h"
#include "UIBaseMsgBox.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUIBaseMsgBox : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	virtual void SetDesc(const FString& InMsg);

	//void SetJustification(ETextJustify::Type InJustification);

	//EUIMsgBoxType GetMsgBoxType() { return MsgBoxType; }
	//void SetMsgBoxType(EUIMsgBoxType InMsgBoxType) { MsgBoxType = InMsgBoxType; }

protected:
	URichTextBlock* text_message;
};
