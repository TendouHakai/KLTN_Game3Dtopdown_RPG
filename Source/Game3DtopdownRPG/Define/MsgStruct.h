// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MsgStruct.generated.h"

UENUM(BlueprintType)
enum class EMsgEventButtonType : uint8
{
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	Exit		UMETA(DisplayName = "Exit"),
};

UENUM(BlueprintType)
enum class EUIMsgBoxType : uint8
{
	None = 0,
	Basic						UMETA(DisplayName = "Basic"),
};