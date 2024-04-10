// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
	, bValidWidget(true)
{
}

bool UBaseWidget::Initialize()
{
	return Super::Initialize();;
}

void UBaseWidget::Init()
{

}

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseWidget::Destroy(UUIBaseMgr* InUIManager)
{
	RemoveFromParent();
	RemoveFromViewport();
}

void UBaseWidget::Update()
{

}
