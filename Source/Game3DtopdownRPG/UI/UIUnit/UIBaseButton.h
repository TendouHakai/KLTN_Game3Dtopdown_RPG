// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/TextBlock.h"
#include "UIBaseButton.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUIBaseButton : public UUIUnitWidget
{
	GENERATED_BODY()
	
protected:
	UTextBlock* Visible_Text;

	UFUNCTION(BlueprintCallable, Category = "BattleAutoPlay")
	void OnTap();
public:
	DECLARE_DELEGATE(FOnClicked);
	FOnClicked OnClicked_Delegate;
};
