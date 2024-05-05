// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Category;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ItemGrape;
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