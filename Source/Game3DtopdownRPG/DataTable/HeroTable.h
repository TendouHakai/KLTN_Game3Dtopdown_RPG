// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HeroTable.generated.h"

// Hero Data

UENUM(BlueprintType)
enum class ECharacterStat : uint8
{
	STR = 0,
	INT,
	VIT,
	AGI,
	Max
};

UENUM(BlueprintType)
enum class ECharacterParam : uint8
{
	PhysicDamage = 0,
	MagicDamage,
	HP,
	Def,
	MagicDef,
	AttackSpeed,
	MovementSpeed,
	ReduceCoolDownRatio,
	CriticalRatio,
	HealHP,
	PierceDef,
	PiercingMagicDef,
	DebuffResistanceRatio,
	Max
};

USTRUCT(BlueprintType)
struct FCharacterParam
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float PhysicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MagicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float HP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Def;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MagicDef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float AttackSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MovementSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float ReduceCoolDownRatio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CriticalRatio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float HealHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float PierceDef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float PierceMagicDef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float DebuffResistanceRatio;
};


USTRUCT(BlueprintType)
struct FHero : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FCharacterParam BaseParam;
};

USTRUCT(BlueprintType)
struct FHeroLevel : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float SumExp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float NextExp;
};

USTRUCT(BlueprintType)
struct FHeroParamLevel : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FCharacterParam ParamUpgrape;
};

USTRUCT(BlueprintType)
struct FBuffInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 BuffCondition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString BuffText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString BuffIcon;
};