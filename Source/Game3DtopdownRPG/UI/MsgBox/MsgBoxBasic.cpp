// Fill out your copyright notice in the Description page of Project Settings.


#include "MsgBoxBasic.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"

bool UMsgBoxBasic::Initialize()
{
	bool bInitialize = Super::Initialize();
	if (bInitialize)
	{
		buttonLeft = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_left"));
		if (nullptr != buttonLeft)
		{
			buttonLeft->InitUnit(GameMode);
			buttonLeft->OnClicked_Delegate.Unbind();
			buttonLeft->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapLeftButton")));
		}

		buttonRight = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_right"));
		if (nullptr != buttonRight)
		{
			buttonRight->InitUnit(GameMode);
			buttonRight->OnClicked_Delegate.Unbind();
			buttonRight->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapRightButton")));
		}
	}
	return bInitialize;
}

void UMsgBoxBasic::Destroy(class UUIBaseMgr* InUIManager)
{
	if (HandlerLeft.IsBound())
		HandlerLeft.Unbind();
	if (HandlerRight.IsBound())
		HandlerRight.Unbind();
	Super::Destroy(InUIManager);
}

void UMsgBoxBasic::OnTapLeftButton()
{
	if(HandlerLeft.IsBound())
		HandlerLeft.ExecuteIfBound();

	DoClose();
}

void UMsgBoxBasic::OnTapRightButton()
{
	if (HandlerRight.IsBound())
		HandlerRight.ExecuteIfBound();
	
	DoClose();
}

void UMsgBoxBasic::SetButtonType(EUIMsgBoxBtnType InButtonType)
{
	if (nullptr == buttonLeft || nullptr == buttonRight) return;
	if (EUIMsgBoxBtnType::Confirm == InButtonType)
	{
		buttonLeft->SetVisibility(ESlateVisibility::Visible);
		buttonLeft->SetTextButton(TEXT("Confirm"));
		buttonRight->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if (EUIMsgBoxBtnType::OkOrCancel == InButtonType)
	{
		buttonLeft->SetVisibility(ESlateVisibility::Visible);
		buttonLeft->SetTextButton(TEXT("Ok"));
		buttonRight->SetVisibility(ESlateVisibility::Visible);
		buttonRight->SetTextButton(TEXT("Cancel"));
	}
	else if (EUIMsgBoxBtnType::QuitOrStart == InButtonType)
	{
		buttonLeft->SetVisibility(ESlateVisibility::Visible);
		buttonLeft->SetTextButton(TEXT("Start"));
		buttonRight->SetVisibility(ESlateVisibility::Collapsed);
		buttonRight->SetTextButton(TEXT("Quit"));
	}
	else if (EUIMsgBoxBtnType::YesOrNo == InButtonType)
	{
		buttonLeft->SetVisibility(ESlateVisibility::Visible);
		buttonLeft->SetTextButton(TEXT("Yes"));
		buttonRight->SetVisibility(ESlateVisibility::Collapsed);
		buttonRight->SetTextButton(TEXT("No"));
	}
}
