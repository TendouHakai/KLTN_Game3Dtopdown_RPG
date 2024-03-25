// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUIWidget : public UBaseWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void NativeConstruct() override;
};
