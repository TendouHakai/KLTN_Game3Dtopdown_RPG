// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API ULoadingWidget : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LoadingWidget")
	float GetLoadingRatio();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LoadingWidget")
	FString GetTextLoadingPercent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "LoadingWidget")
	void StartChangeScene();

private:
	UProgressBar* ProgressBar;
	class UTextBlock* TextPercent;

	float StartTime = 0;
	float TimeToLoaing = 2;
	bool isEndLoading = false;
};
