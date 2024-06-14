// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffStruct.generated.h"

UENUM(BlueprintType)
enum class EHeroBuffType : uint8
{
	Damage_Increase		= 0 UMETA(DisplayName = "0.Damage_Increase"),
	Damage_Decrease		= 1 UMETA(DisplayName = "1.Damage_Decrease"),
	Flame				= 2 UMETA(DisplayName = "2.Flame"),
	Freezing			= 3 UMETA(DisplayName = "3.Freezing"),
	Stun				= 4 UMETA(DisplayName = "4.Stun"),
	Slow				= 5 UMETA(DisplayName = "5.Slow"),
	Bleeding			= 6 UMETA(DisplayName = "6.Bleeding"),
	Silence				= 7 UMETA(DisplayName = "7.Silence"),
	Blindness			= 8 UMETA(DisplayName = "8.Blindness"),
	HP_Recovery			= 9 UMETA(DisplayName = "9.HP_Recovery"),
	HP_Recovery_Loop	= 10 UMETA(DisplayName = "10.HP_Recovery_Loop"),
	Invincible			= 11 UMETA(DisplayName = "11.Invincible"),
	AtkSpeed_Increase	= 12 UMETA(DisplayName = "12.AtkSpeed_Increase"),
	CCImmune			= 13 UMETA(DisplayName = "13.CCImmune"),
	HealBan				= 14 UMETA(DisplayName = "14.HealBan"),
	Shield				= 15 UMETA(DisplayName = "15.Shield"),
	MoveSpeedIncrease	= 16 UMETA(DisplayName = "16.MoveSpeedIncrease"),
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHeroBuffType BuffType = EHeroBuffType::None_Buff;
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
	Inc_PhysicsDamage,
	Inc_MagicDamage,
	Inc_AllDamage,
	Freezing,
	Stun,
	Slow,
	Rec_HealthPoint,
	Rec_HealthPoint_Loop,
	Invincible,
	Shield,
	Inc_AtkSpeed,
	Immune,
	Bleeding, 
	Blindness,
	Max
};