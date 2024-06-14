// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimSpeedBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"

void UAnimSpeedBuff::ApplyOwnerSpeed(float Speed)
{
	OwnerCharacter->GetMesh()->GlobalAnimRateScale = Speed;

	SetChildActorGlobalAnimRateScale(Speed);
}

void UAnimSpeedBuff::BeginBuff()
{
	Super::BeginBuff();

	OwnerCharacter->UpdateAttackSpeedRate();
	OwnerCharacter->UpdateMoveSpeedRate();
}

void UAnimSpeedBuff::EndBuff(bool bForcedEnd)
{
	Super::EndBuff(bForcedEnd);

	OwnerCharacter->UpdateAttackSpeedRate();
	OwnerCharacter->UpdateMoveSpeedRate();
}

float UAnimSpeedBuff::CalculateSpeedBuffAmount(const UClass* ClassType)
{
	TArray<UBaseBuff*> AnimSpeedBuffArray;
	OwnerCharacter->FindHaveBuff(ClassType, AnimSpeedBuffArray);

	float totalSpeed = 1.0f;
	for (int i = 0; i < AnimSpeedBuffArray.Num(); ++i)
	{
		UAnimSpeedBuff* AnimSpeedBuff = Cast<UAnimSpeedBuff>(AnimSpeedBuffArray[i]);

		if (nullptr == AnimSpeedBuff || this == AnimSpeedBuff)
			continue;

		totalSpeed += AnimSpeedBuff->GetUpdateSpeed();
	}

	return totalSpeed;
}

bool UAnimSpeedBuff::IsFreezeState()
{
	return (0 >= OwnerCharacter->GetMesh()->GlobalAnimRateScale) ? true : false;
}

void UAnimSpeedBuff::UpdateAnimSpeed()
{
	if (nullptr == OwnerCharacter)
		return;

	USkeletalMeshComponent* OwnerMesh = OwnerCharacter->GetMesh();
	if (!OwnerMesh || !OwnerMesh->IsVisible())
		return;

	UBaseAnimInstance* AnimInstance = OwnerCharacter->GetAnimInstance();

	if (nullptr == AnimInstance)
		return;

	if (true == IsFreezeState())
		return;

	float totalSpeed = GetAnimSpeed();

	ApplyOwnerSpeed(totalSpeed);
}

void UAnimSpeedBuff::SetChildActorGlobalAnimRateScale(float Speed)
{
	TArray<AActor*> ChildActorArray;
	OwnerCharacter->GetAllChildActors(ChildActorArray);

	for (AActor* ChildActor : ChildActorArray)
	{
		USkeletalMeshComponent* TargetMesh = Cast<USkeletalMeshComponent>(ChildActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		if (nullptr == TargetMesh)
			continue;

		TargetMesh->GlobalAnimRateScale = Speed;
	}
}
