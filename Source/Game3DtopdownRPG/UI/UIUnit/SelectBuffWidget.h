// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffStruct.h"
#include "SelectBuffWidget.generated.h"

class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API USelectBuffWidget : public UUIUnitWidget
{
	GENERATED_BODY()
	
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnTapSelect();

	void SetInfo(FHeroBuffInfo buffinfo);
	void SetCharacter(ABaseCharacter* Caster);

protected:
	// UI
	UTextBlock* textNameBuff;
	UImage* imageBuff;
	URichTextBlock* richtextDecrip;
	UTextBlock* textDuration;

	//  info
	FHeroBuffInfo infoBuff;
	ABaseCharacter* caster;
public:
	DECLARE_DELEGATE(FOnClicked);
	FOnClicked OnClicked_Delegate;
};
