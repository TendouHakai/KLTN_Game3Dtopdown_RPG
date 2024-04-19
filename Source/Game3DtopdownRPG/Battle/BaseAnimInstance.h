// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EChrAnimState : uint8
{
	StandRun				UMETA(DisplayName = "StandRun"),
	StartRun				UMETA(DisplayName = "StartRun"),
	EndRun					UMETA(DisplayName = "EndRun"),
	Die						UMETA(DisplayName = "Die"),
	Hit1					UMETA(DisplayName = "Hit1"),
	Hit2					UMETA(DisplayName = "Hit2"),
	Hit3					UMETA(DisplayName = "Hit3"),
	Hit4					UMETA(DisplayName = "Hit4"),
	HitKnockdown			UMETA(DisplayName = "HitKnockdown"),
	HitStun					UMETA(DisplayName = "HitStun"),
	HitAir					UMETA(DisplayName = "HitAir"),
	HitRecovery				UMETA(DisplayName = "HitRecovery"),
	Attack1					UMETA(DisplayName = "Attack1"),
	Attack2					UMETA(DisplayName = "Attack2"),
	Attack3					UMETA(DisplayName = "Attack3"),
	Attack4					UMETA(DisplayName = "Attack4"),
	Attack5					UMETA(DisplayName = "Attack5"),
	Attack6					UMETA(DisplayName = "Attack6"),
	Skill1					UMETA(DisplayName = "Skill1"),
	Skill2					UMETA(DisplayName = "Skill2"),
	Skill3					UMETA(DisplayName = "Skill3"),
	Dash					UMETA(DisplayName = "Dash"),
	Roar					UMETA(DisplayName = "Roar"),
	RangeAtk				UMETA(DisplayName = "RangeAtk"),
	ExtraCombo				UMETA(DisplayName = "ExtraCombo"),
	Victory					UMETA(DisplayName = "Victory"),
	Riposte					UMETA(DisplayName = "Riposte"),
	Dodge					UMETA(DisplayName = "Dodge"),
	Guard					UMETA(DisplayName = "Guard"),
	FakeDie					UMETA(DisplayName = "FakeDie"),
	Resurrect				UMETA(DisplayName = "Resurrect"),
};

UCLASS(meta = (BlueprintThreadSafe))
class GAME3DTOPDOWNRPG_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsAnimMovable();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsAnimAttackState();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsAnimSkillState();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsAnimHitState();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsStateAvailableToCombo();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsAnimRangeAtkState();

	UFUNCTION(BlueprintPure, Category = "BaseAnimInstance")
	bool IsStun();


	UFUNCTION(BlueprintImplementableEvent, Category = "SBAnimInstance")
	float GetRunningSpeed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SBAnimInstance")
	void ChangeAnimState(EChrAnimState ChangeState);

	UFUNCTION(BlueprintCallable, Category = "SBAnimInstance")
	void PrintAnimStateLog(FString LogStr, EChrAnimState LogAnimState);

	UFUNCTION(BlueprintPure, Category = "SBAnimInstance")
	int32 StateMachineCurrentState();

	const FAnimNode_StateMachine* GetStateMachine(FName MachineName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EChrAnimState AnimState;

	UPROPERTY(EditDefaultsOnly)
	bool bPrintAnimStateLog = false;
};
