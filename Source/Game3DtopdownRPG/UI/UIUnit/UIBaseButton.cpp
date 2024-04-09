// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBaseButton.h"

void UUIBaseButton::OnTap()
{
	OnClicked_Delegate.ExecuteIfBound();
}
