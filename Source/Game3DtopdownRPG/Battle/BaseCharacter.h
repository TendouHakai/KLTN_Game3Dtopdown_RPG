// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitFreezer.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"
#include "BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharTeam : uint8
{
	Ally,
	Enemy,
};

UCLASS()
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	ECharTeam CharTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroInfo") FName HeroID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroInfo") uint8 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroInfo") uint8 CurExp;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float AttackSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float MovementSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float ReduceCoolDownSkillRatio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float HealHPPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float DebuffResistanceRatio;
	
private:
	UPROPERTY() USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY() UHitFreezer* HitFreezer;
};
