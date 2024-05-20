// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "HeroMgr.generated.h"

class ABaseCharacter;
struct FGameItemEquipmentInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UHeroMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	// Equip item 
	UFUNCTION(BlueprintCallable)
	void EquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	void ChangeHeroParam(FCharacterParam& heroParam, const FCharacterParam& AddParam, bool IsAddParam = true);

protected:

};
