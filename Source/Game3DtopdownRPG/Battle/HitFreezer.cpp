// Fill out your copyright notice in the Description page of Project Settings.


#include "HitFreezer.h"
#include "HitFlash.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UHitFreezer::UHitFreezer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHitFreezer::HitFreeze(float FreezeDuration, bool bApplyColor)
{
	USkeletalMeshComponent* TargetMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!TargetMesh) return;

	if (bApplyColor) // »ö±ò ¹øÂ½ÀÌµµ·Ï
	{
		UHitFlash* HitFlash = Cast<UHitFlash>(GetOwner()->GetComponentByClass(UHitFlash::StaticClass()));

		if (HitFlash)
			HitFlash->Flash(HitFreezeColor, FMath::Max(FreezeDuration, 1.0f / 30.0f));
	}

	if (FreezeDuration <= 0) return;

	if (EndHitFreezeTimer.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(EndHitFreezeTimer);

	GetWorld()->GetTimerManager().SetTimer(EndHitFreezeTimer, this, &UHitFreezer::EndHitFreeze, FreezeDuration, false);
}

void UHitFreezer::BeginPlay()
{
	Super::BeginPlay();

}

void UHitFreezer::EndHitFreeze()
{
	GetWorld()->GetTimerManager().ClearTimer(EndHitFreezeTimer);

	float AnimRateScale = 1.0f;

	//if (ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
	//{
	//	TArray<UCBaseBuff*> BuffArray;
	//	OwnerCharacter->FindHaveBuff(UCAnimSpeedBuff::StaticClass(), BuffArray);

	//	for (UCBaseBuff* BaseBuff : BuffArray)
	//	{
	//		UCAnimSpeedBuff* AnimSpeedBuff = Cast<UCAnimSpeedBuff>(BaseBuff);
	//		AnimRateScale += AnimSpeedBuff->GetUpdateSpeed();
	//	}
	//}

	SetActorGlobalAnimRateScale(AnimRateScale);
}

void UHitFreezer::SetActorGlobalAnimRateScale(float GlobalAnimRateScale)
{
	USkeletalMeshComponent* TargetMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!TargetMesh) return;

	TargetMesh->GlobalAnimRateScale = GlobalAnimRateScale;
	SetChildActorGlobalAnimRateScale(GlobalAnimRateScale);
}

void UHitFreezer::SetChildActorGlobalAnimRateScale(float GlobalAnimRateScale)
{
	TArray<AActor*> ChildActorArray;
	GetOwner()->GetAllChildActors(ChildActorArray);

	for (AActor* ChildActor : ChildActorArray)
	{
		USkeletalMeshComponent* TargetMesh = Cast<USkeletalMeshComponent>(ChildActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		if (nullptr == TargetMesh)
			continue;

		TargetMesh->GlobalAnimRateScale = GlobalAnimRateScale;
	}
}

void UHitFreezer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (false == EndHitFreezeTimer.IsValid())
		return;

	SetActorGlobalAnimRateScale(HitFreezeAnimRateScale);
}

