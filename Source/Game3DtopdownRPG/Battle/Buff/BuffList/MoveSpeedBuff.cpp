// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSpeedBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"

void UMoveSpeedBuff::BeginBuff()
{
	Super::BeginBuff();

	/*float totalSpeed = CalculateSpeedBuffAmount(StaticClass()) + GetUpdateSpeed();
	OwnerCharacter->SetMoveSpeedModifier(totalSpeed);*/
}

void UMoveSpeedBuff::EndBuff(bool bForcedEnd /*= false*/)
{
	//float totalSpeed = CalculateSpeedBuffAmount(StaticClass());
	//OwnerCharacter->SetMoveSpeedModifier(totalSpeed);

	Super::EndBuff(bForcedEnd);
}

float UMoveSpeedBuff::GetAnimSpeed()
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
	if (AnimInstance->IsAnimMovable())
	{
		totalSpeed = CalculateSpeedBuffAmount(StaticClass());

		if (bActiveBuff)
			totalSpeed += GetUpdateSpeed();
	}

	return totalSpeed;
}
