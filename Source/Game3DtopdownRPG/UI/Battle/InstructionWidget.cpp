// Fill out your copyright notice in the Description page of Project Settings.


#include "InstructionWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"

void UInstructionWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	BackButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Close"));

	if (nullptr != BackButton)
	{
		BackButton->OnClicked_Delegate.BindUFunction(this, TEXT("OnBackBtn"));
	}
}

bool UInstructionWidget::Initialize()
{
	bool Initialize = Super::Initialize();
	if (Initialize)
	{
		CacheOwnUI();
	}
	return Initialize;
}

void UInstructionWidget::OnBackBtn()
{
	if (UIMgr != nullptr)
		UIMgr->OpenUI(EUIName::PauseMenu);

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}
