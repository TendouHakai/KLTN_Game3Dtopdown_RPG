// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "SettingMenu.generated.h"

class UUIBaseButton;

UCLASS()
class GAME3DTOPDOWNRPG_API USettingMenu : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual bool Initialize() override;
	virtual void Update() override;

	UFUNCTION() void OnBackButton();
	UFUNCTION(BlueprintCallable) void OnTapgraphicQuality(int index);
	UFUNCTION(BlueprintCallable) void OnTapScreenSpeed(int index);
	UFUNCTION(BlueprintCallable) void OnChangeResolution(FString resolution);

	UFUNCTION(BlueprintCallable) void OnValueChangeSoundSFXVolume(float InValue);
	UFUNCTION(BlueprintCallable) void OnValueChangeSoundMusicVolume(float InValue);

	UFUNCTION(BlueprintCallable) void SetSoundSFX(float InValue);
	UFUNCTION(BlueprintCallable) void SetSoundMusic(float InValue);

protected:
	UUIBaseButton* BackButton;
	USlider* sliderSFXBar;
	UProgressBar* SoundBar;
	USlider* sliderMusicBar;
	UProgressBar* MusicBar;

	TArray<UImage*> imageSelectGraphic;
	TArray<UImage*> imageSelectScreenSpeed;
private:
	enum class EMaxFps : uint8
	{
		VeryLow = 10,
		Low = 30,
		Medium = 60,
		High = 120,
		VeryHigh = 200,
	};
};
