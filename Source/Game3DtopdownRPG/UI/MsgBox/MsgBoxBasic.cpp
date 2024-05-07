// Fill out your copyright notice in the Description page of Project Settings.


#include "MsgBoxBasic.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"

bool UMsgBoxBasic::Initialize()
{
	bool bInitialize = Super::Initialize();
	if (bInitialize)
	{
		button = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton"));
		if (nullptr != button)
		{
			button->OnClicked_Delegate.Unbind();
			button->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTap")));
		}
	}
	return bInitialize;
}

void UMsgBoxBasic::Destroy(class UUIBaseMgr* InUIManager)
{
	Super::Destroy(InUIManager);
	if(HandlerLeft.IsBound())
		HandlerLeft.Unbind();
}

void UMsgBoxBasic::OnTap()
{
	if(HandlerLeft.IsBound())
		HandlerLeft.ExecuteIfBound();
}
