// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "PauseMenu.generated.h"

class UUIBaseButton;

UCLASS()
class GAME3DTOPDOWNRPG_API UPauseMenu : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual bool Initialize() override;

	UFUNCTION() void OnResumeButton();
	UFUNCTION() void OnBackButton();
	UFUNCTION() void OnSettingButton();

protected:
	UUIBaseButton* ResumeButton;
	UUIBaseButton* BackButton;
	UUIBaseButton* SettingButton;
};
