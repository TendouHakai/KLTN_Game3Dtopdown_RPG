// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingWidget.h"

void ULoadingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartTime = 0;
	isEndLoading = false;
}

void ULoadingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!isEndLoading)
	{
		if (StartTime < TimeToLoaing)
		{
			StartTime += InDeltaTime;
		}
		else
		{
			isEndLoading = true;
			StartChangeScene();
		}
	}
	
}

float ULoadingWidget::GetLoadingRatio()
{
	float Ratio = StartTime / TimeToLoaing;
	return FMath::Clamp<float>(Ratio, 0.0f, 1.0f);
}

FString ULoadingWidget::GetTextLoadingPercent()
{
	int percent = GetLoadingRatio() * 100;
	percent = FMath::Clamp<int>(percent, 0, 100);
	FString str = FString::Printf(TEXT("Loading... %d"), percent);
	return FString::Printf(TEXT("Loading... %d"), percent);
}
