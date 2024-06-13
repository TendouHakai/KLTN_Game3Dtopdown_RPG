// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitFreezer.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"
#include "BattleStruct.h"
#include "Game3DtopdownRPG/Define/HeroStruct.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "BaseCharacter.generated.h"

class UBuffControllerComponent;

UENUM(BlueprintType)
enum class ECharTeam : uint8
{
	Ally,
	Enemy,
};

UCLASS(Blueprintable, BlueprintType)
class GAME3DTOPDOWNRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float value) {
		if (value != 0) {
			FVector forwardV = FVector(0, -1, 0);
			AddMovementInput(value * forwardV);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float value) {
		if (value != 0) {
			FVector rightV = FVector(1, 0, 0);
			AddMovementInput(value * rightV);
		}
	}
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Stat function
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure, Category = "Character")
	float getHP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure, Category = "Character")
	float getMaxHP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void SetHP(float HP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void SetMaxHP(float MaxHP); 

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetHealthRatio();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetShieldRatio();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetCharTeam(ECharTeam InCharTeam) { this->CharTeam = InCharTeam; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	ECharTeam GetCharTeam() { return CharTeam; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool GetEnemyTeam(ECharTeam& OutEnemyTeam);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	bool IsCharacterDamageable();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void HitFreeze(float FreezeDuration, bool bApplyColor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	UBaseAnimInstance* GetAnimInstance();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetMovementSpeedRate() { return MovementSpeedRate; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetMovementSpeedRate(float MovementSpeed);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void CharacterHealHpPerSecond();

	// Skill
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StartSkillAdditionalProcess(int32 SkillIdx);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void EndSkillAdditionalProcess();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	FNativeSkillInfo GetNativeSkillInfo(int32 InIndex);

	// buff
	UFUNCTION(BlueprintCallable, Category = "Character")
	void AddBuffToAttacker(ABaseCharacter* Attacker, const FHeroBuffInfo& HeroBuffInfo);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void AddBuffToDefender(ABaseCharacter* Attacker, const FHeroBuffInfo& HeroBuffInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	bool IsCharacterAlive();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, Category = "Character")
	EChrAnimState GetAnimState();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, Category = "Character")
	FHeroInfo GetHeroInfo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void SetHeroInfo(FHeroInfo info);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void EquipItem(FGameItemEquipmentInfo iteminfo, bool IsInit = true);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void UnEquipItem(FGameItemEquipmentInfo iteminfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void EquipNormalItem(FGameItemInfo iteminfo, int32 postion, bool IsInit = true);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void UnEquipNormalItem(FGameItemInfo iteminfo, int32 postion);

	// get current class
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	EHeroClass GetCurrentHeroClass();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void FindHaveBuff(const UClass* ClassType, TArray<UBaseBuff*>& BuffArray);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetDeBuffResistRatio() { return DebuffResistanceRatio/100.f; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void ReceiveDamage(ABaseCharacter* Caster, float Amount, bool bMagicDamage, bool bForcedBuff = false);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void BeginStun();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void EndStun();

	void PlayStunStartSound();

	void UpdateAttackSpeedRate();
	void UpdateMoveSpeedRate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void CharacterHeal(float HealPercent);

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsInvincible();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetShield();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetShield(float shieldHP);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	float GetMaxShield();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetMaxShield(float maxShieldHP);

	void SetIsShieldOn(bool bOn) { bShieldOn = bOn; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	bool GetIsShieldOn() { return bShieldOn; }

protected:
	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsValidBuff(const FHeroBuffInfo& HeroBuffInfo);

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsEnemyBuff(const FHeroBuffInfo& HeroBuffInfo);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	ECharTeam CharTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UBuffControllerComponent* HeroBuffController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default") USoundBase* StunStartSound;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroInfo") int32 HeroID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroInfo", meta = (ExposeOnSpawn = true)) int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float AttackSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float MoveSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float MovementSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float ReduceCoolDownSkillRatio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float HealHPPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float DebuffResistanceRatio;

protected:
	float ShieldHP;
	float MaxShieldHP;
	bool bShieldOn;
	
private:
	UPROPERTY() USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY() UHitFreezer* HitFreezer;
};
