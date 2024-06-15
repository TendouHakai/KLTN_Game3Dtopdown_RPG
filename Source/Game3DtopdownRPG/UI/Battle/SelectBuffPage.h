// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "SelectBuffPage.generated.h"

class USelectBuffWidget;
class ABaseCharacter;
struct FHeroBuffInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API USelectBuffPage : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetCaster(ABaseCharacter* Caster);

	UFUNCTION(BlueprintCallable)
	void SetBuffInfos(TArray<FHeroBuffInfo> buffinfos);

	UFUNCTION()
	void OnSelectBuff();

protected:
	// UI
	TArray< USelectBuffWidget*> selectbuffs;

	// info
	ABaseCharacter* caster;
};
