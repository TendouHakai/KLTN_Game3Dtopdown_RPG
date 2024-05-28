// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "HeroTable.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "ItemTable.generated.h"
/**
 * 
 */


USTRUCT(BlueprintType)
struct FItemInfoRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DesName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemCategory Category;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemGrade ItemGrape;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 MaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 SellGold;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 BuyGold;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool CanMake;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString ItemIcon;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Description;	
};

USTRUCT(BlueprintType)
struct FItemTypeInfoRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DesNameType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool IsEnableUseButton;
};

UENUM(BlueprintType)
enum class EItemEquipPosition : uint8
{
	HeadGears,
	ShoulderPad,
	Shoe,
	Glove,
	Belt,
	Backpack,
	Weapon,
	Shield,
	Clother,
	All,
	Max
};

USTRUCT(BlueprintType)
struct FItemEquipmentInfoRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DesName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 EquipmentLevel;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemGrade EquipmentGrape;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemEquipPosition EquipPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FCharacterParam ItemEquipParam;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 NextItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 NeedGold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<int32> Materials;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<int32> MatCounts;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USkeletalMesh* MeshSkeletal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMesh* MeshStatic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString IconName;
};

USTRUCT(BlueprintType)
struct FItemEquipmentLevRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float expStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float expEnd;
};

USTRUCT(BlueprintType)
struct FUpgradeLevelOfMaterialRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ItemReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float expUpgrade;
};