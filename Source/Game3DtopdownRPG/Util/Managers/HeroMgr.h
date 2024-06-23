// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "HeroMgr.generated.h"

class ABaseCharacter;
struct FGameItemEquipmentInfo;

UENUM(BlueprintType)
enum class EStartPosition : uint8
{
	StartZone,
	StartZone_Stage,
	Max,
};

UCLASS()
class GAME3DTOPDOWNRPG_API UHeroMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	// record
	FHeroRecord* GetHeroRecord(FName HeroIndex);
	FHeroParamLevelRecord* GetHeroLevelParamRecord(FName HeroLevIndex);
	FSkillInfoRecord* GetSkillInfoRecord(FName skillIndex);
	FSkillInfoRecord* GetSkillInfoRecord(EHeroClass heroclass, uint8 skillIndex);

	// Level Up Param
	UFUNCTION(BlueprintCallable)
	void LevelUpHeroParam(ABaseCharacter* hero, int32 levelup);

	UFUNCTION(BlueprintCallable)
	void LevelUpItemEquipmentHeroParam(ABaseCharacter* hero, FGameItemEquipmentInfo info);

	// Equip item 
	UFUNCTION(BlueprintCallable)
	void EquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	void UnEquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	void UnEquipHeroItemByClass(ABaseCharacter* hero);

	// Equip normal item
	UFUNCTION(BlueprintCallable)
	void EquipHeroNormalItem(ABaseCharacter* hero, FGameItemInfo iteminfo, int32 position);

	UFUNCTION(BlueprintCallable)
	void UnEquipHeroNormalItem(ABaseCharacter* hero, FGameItemInfo iteminfo, int32 position);

	UFUNCTION(BlueprintCallable)
	void UseEquipHeroNormalItem(ABaseCharacter* hero, int32 position);

	UFUNCTION(BlueprintCallable)
	void ChangeHeroParam(FCharacterParam& heroParam, const FCharacterParam& AddParam, bool IsAddParam = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsStartZone = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EStartPosition startPosition = EStartPosition::StartZone;
};
