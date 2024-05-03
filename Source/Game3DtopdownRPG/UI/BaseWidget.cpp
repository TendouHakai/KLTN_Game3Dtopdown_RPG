// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
	, bValidWidget(true)
{
}

bool UBaseWidget::Initialize()
{
	bool IsInitialized = Super::Initialize();
	if (IsInitialized)
	{
	
	}

	return IsInitialized;
}

void UBaseWidget::Init()
{
	OnInitialize();

	CacheOwnUI();
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

void UBaseWidget::OnInitialize_Implementation()
{
}

UWidgetAnimation* UBaseWidget::GetWidgetAnimation(const FString& InAnimationName)
{
	if (UWidgetBlueprintGeneratedClass* BGClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		for (UWidgetAnimation* Animation : BGClass->Animations)
		{
			if (Animation->MovieScene->GetName() == InAnimationName)
				return Animation;
		}
	}

	bValidWidget = false;
	return nullptr;
}
