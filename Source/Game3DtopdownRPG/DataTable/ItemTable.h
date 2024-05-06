// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 SaleGold;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 BuyGold;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool CanMake;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString ItemIcon;	
};

USTRUCT(BlueprintType)
struct FItemTypeInfoRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DesNameType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool IsEnableUseButton;
};