// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ExpProgressBar.generated.h"

struct FHeroInfo;


UCLASS()
class GAME3DTOPDOWNRPG_API UExpProgressBar : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetHeroExpInfo(FHeroInfo HeroInfo);

	UFUNCTION(BlueprintCallable)
	virtual void SetAddExp(int32 AddExp);

	UFUNCTION(BlueprintCallable)
	virtual void SetLevel(int32 level);

	float GetRatioProgressBar(float cExp);

protected:
	void UpdateInfo();

protected:
	int32 curExp;
	float Exp;
	int32 startExp;
	int32 endExp;
	int32 addExp = 0;

	int32 Level;
	int32 curLevel;

	UProgressBar* progressbar;
	UTextBlock* textLevel;

	bool bStartAddExp;
};
