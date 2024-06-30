// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Game3DtopdownRPG/Define/HeroStruct.h"
#include "SavedUserConfig.generated.h"

UCLASS()
class GAME3DTOPDOWNRPG_API USavedUserConfig : public USaveGame
{
	GENERATED_BODY()

public:
	USavedUserConfig();

	UFUNCTION(BlueprintCallable, Category = "SavedUserConfig")
	static void SaveUserCfgToFile(USavedUserConfig* Cfg);

	UFUNCTION(BlueprintCallable, Category = "SavedUserConfig")
	static USavedUserConfig* LoadUserCfgFromFile(bool& bSuccess);

	UFUNCTION(BlueprintCallable, Category = "SavedUserConfig")
	static void InitUserCfgFile();

	// Hero
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInitHero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHeroInfo HeroInfo;

	// setting
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BGMVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IndexGraphic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IndexScreenSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString strResolution;

	// intro sceen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFirstTime;
};
