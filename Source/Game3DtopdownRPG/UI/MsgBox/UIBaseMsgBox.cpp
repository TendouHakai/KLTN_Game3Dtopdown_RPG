// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBaseMsgBox.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"

bool UUIBaseMsgBox::Initialize()
{
	bool bInitialize = Super::Initialize();
	if (bInitialize)
	{
		text_message = GetOwnUI<URichTextBlock>(TEXT("RichTextBlock_Description"));
	}
	return bInitialize;
}

void UUIBaseMsgBox::SetDesc(const FString& InMsg)
{
	text_message->SetText(FText::FromString(InMsg));
}

void UUIBaseMsgBox::DoClose()
{
	if (UIMgr)
	{
		Destroy(UIMgr);
		UIMgr->CloseMsgBox(GetName());
	}
	else Destroy(nullptr);
}
