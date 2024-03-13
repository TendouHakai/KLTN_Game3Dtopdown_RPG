// Fill out your copyright notice in the Description page of Project Settings.


#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"

bool UBaseAnimInstance::IsAnimMovable()
{
	return (AnimState == EChrAnimState::StandRun);
}

bool UBaseAnimInstance::IsAnimAttackState()
{
	return (static_cast<uint8>(AnimState) >= static_cast<uint8>(EChrAnimState::Attack1)) && (static_cast<uint8>(AnimState) <= static_cast<uint8>(EChrAnimState::Attack6));
}

bool UBaseAnimInstance::IsAnimSkillState()
{
	return (static_cast<uint8>(AnimState) >= static_cast<uint8>(EChrAnimState::Skill1)) && (static_cast<uint8>(AnimState) <= static_cast<uint8>(EChrAnimState::Skill3));
}

bool UBaseAnimInstance::IsAnimHitState()
{
	return (static_cast<uint8>(AnimState) >= static_cast<uint8>(EChrAnimState::Hit1)) && (static_cast<uint8>(AnimState) <= static_cast<uint8>(EChrAnimState::HitAir));
}

bool UBaseAnimInstance::IsStateAvailableToCombo()
{
	return IsAnimMovable() || IsAnimAttackState();
}

bool UBaseAnimInstance::IsAnimRangeAtkState()
{
	return (AnimState == EChrAnimState::RangeAtk);
}

bool UBaseAnimInstance::IsStun()
{
	return (AnimState == EChrAnimState::HitStun);
}

void UBaseAnimInstance::PrintAnimStateLog(FString LogStr, EChrAnimState LogAnimState)
{
}

int32 UBaseAnimInstance::StateMachineCurrentState()
{
	return int32();
}

const FAnimNode_StateMachine* UBaseAnimInstance::GetStateMachine(FName MachineName)
{
	return nullptr;
}
