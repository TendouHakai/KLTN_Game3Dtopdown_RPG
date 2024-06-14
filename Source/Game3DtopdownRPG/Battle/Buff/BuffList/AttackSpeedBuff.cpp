// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackSpeedBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"

void UAttackSpeedBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	Super::RenewBuff(RenewBuffInfo);

	float NewBuffAmount = 0.0f;
	if (RenewBuffInfo.BuffAmount.IsValidIndex(0))
	{
		NewBuffAmount = RenewBuffInfo.BuffAmount[0];
	}

	NewBuffAmount *= CurrentStack;
	ConvertToPercent(NewBuffAmount);

	SpeedPercent = NewBuffAmount;
	SetBuffInfoText();
}

float UAttackSpeedBuff::GetAnimSpeed()
{
	if (nullptr == OwnerCharacter)
		return 1.0f;

	USkeletalMeshComponent* OwnerMesh = OwnerCharacter->GetMesh();
	if (!OwnerMesh || !OwnerMesh->IsVisible())
		return 1.0f;

	UBaseAnimInstance* AnimInstance = OwnerCharacter->GetAnimInstance();

	if (nullptr == AnimInstance)
		return 1.0f;

	if (true == IsFreezeState())
		return 1.0f;

	float totalSpeed = 1.0f;
	if (AnimInstance->IsAnimAttackState())
	{
		totalSpeed = CalculateSpeedBuffAmount(StaticClass());

		if (bActiveBuff)
			totalSpeed += GetUpdateSpeed();
	}

	return totalSpeed;
}
