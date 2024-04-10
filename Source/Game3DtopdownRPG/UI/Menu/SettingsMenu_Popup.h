// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "SettingsMenu_Popup.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API USettingsMenu_Popup : public UUIWidget
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void NativeConstruct() override;
};
