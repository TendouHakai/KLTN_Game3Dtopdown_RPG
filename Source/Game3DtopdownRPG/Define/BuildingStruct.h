// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingStruct.generated.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	Inventory = 0,
	ForgingItem,
	MakingPotion,
	RuneBuff,
	SkillLibrary,
	Max
};