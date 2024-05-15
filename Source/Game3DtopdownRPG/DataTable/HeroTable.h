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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PhysicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MagicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Def;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MagicDef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AttackSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MovementSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ReduceCoolDownRatio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CriticalRatio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float HealHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PierceDef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PierceMagicDef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DebuffResistanceRatio;
};

USTRUCT(BlueprintType)
struct FHeroRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FCharacterParam BaseParam;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 HeroLevParamID;
};

USTRUCT(BlueprintType)
struct FHeroLevelRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float SumExp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float NextExp;
};

// note huong phat trien nhan vat: Knight: 1, Warrior: 2, Archer: 3, Mage: 4

USTRUCT(BlueprintType)
struct FHeroParamLevelRecord : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FCharacterParam ParamUpgrape;
};

USTRUCT(BlueprintType)
struct FBuffInfoRecord : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 BuffCondition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString BuffText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString BuffIcon;
};