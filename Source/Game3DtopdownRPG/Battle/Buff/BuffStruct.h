// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffStruct.generated.h"

UENUM(BlueprintType)
enum class EHeroBuffType : uint8
{
	Damage_Increase		= 0 UMETA(DisplayName = "0.Damage_Increase"),
	Flame				= 1 UMETA(DisplayName = "1.Flame"),
	None_Buff,
};

UENUM(BlueprintType)
enum class EBuffTargetType : uint8
{
	Enemy,
	Self,
	Team,
	Max,
};

USTRUCT(BlueprintType)
struct FHeroBuffInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHeroBuffType BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BuffCondition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBuffTargetType BuffTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<float> BuffAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BuffMaxStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bForcedBuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName AttachedBoneName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EffectPath;

	GENERATED_USTRUCT_BODY() 
public:
	FHeroBuffInfo()
		: BuffType(EHeroBuffType::None_Buff)
		, BuffCondition(0)
		, BuffTarget(EBuffTargetType::Self)
		, Duration(0.0f)
		, BuffMaxStack(1)
		, bForcedBuff(false)
	{
	}
};


UENUM(BlueprintType)
enum class EBuffActorType : uint8
{
	eBuffStateActor = 0,
	eDeBuffAreaActor,
	eDeBuffBoxAreaActor,
	Max,
};

UENUM(BlueprintType)
enum class EBuffEffectType : uint8
{
	Flame = 0,
	Max
};