// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBaseButton.h"

void UUIBaseButton::OnTap()
{
	OnClicked_Delegate.ExecuteIfBound();
}

void UUIBaseButton::CacheOwnUI()
{
	Super::CacheOwnUI();
	Visible_Text = GetOwnUI<UTextBlock>(TEXT("TextBlock_txtButton"));
}

void UUIBaseButton::SetTextButton(FString text)
{
	Visible_Text->SetText(FText::FromString(text));
}
