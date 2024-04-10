// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "../UIUnit/UIBaseButton.h"
#include "MainMenu_Page.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UMainMenu_Page : public UUIWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void Init() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnTapPlayBtn();

	UFUNCTION(BlueprintCallable)
	void OnTapOptionsBtn();

	UFUNCTION(BlueprintCallable)
	void OnTapQuitBtn();

private:
	UUIBaseButton* PlayButton;
	UUIBaseButton* OptionsButton;
	UUIBaseButton* QuitButton;

};
