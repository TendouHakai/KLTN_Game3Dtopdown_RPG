// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeDeBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"

void UFreezeDeBuff::BeginBuff()
{
	Super::BeginBuff();

	OwnerCharacter->GetMesh()->GlobalAnimRateScale = 0.0f;
	if (OwnerCharacter->GetMovementComponent())
	{
		OwnerCharacter->GetMovementComponent()->StopActiveMovement();
	}

	//UCAutoBattleComponent* AutoBattleComp = OwnerCharacter->FindComponentByClass<UCAutoBattleComponent>();
	//if (AutoBattleComp != nullptr)
	//{
	//	AutoBattleComp->OffAutoBattle();
	//}
}

void UFreezeDeBuff::EndBuff(bool bForcedEnd /*= false*/)
{
	if (true == HasOwnerOnlyOneBuffOfThis() && bActiveBuff)
	{
		RestoreActor();
		//UCAutoBattleComponent* AutoBattleComp = OwnerCharacter->FindComponentByClass<UCAutoBattleComponent>();
		//if (AutoBattleComp != nullptr)
		//{
		//	AutoBattleComp->OnAutoBattle();
		//}
	}

	Super::EndBuff(bForcedEnd);
}

void UFreezeDeBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (false == bActiveBuff)
		return;

	ActorFreeze(0.f);
}

void UFreezeDeBuff::RestoreActor()
{
	ActorFreeze(1.f);
	if (0 < OwnerCharacter->getHP() && OwnerCharacter->GetAnimInstance())
		OwnerCharacter->GetAnimInstance()->ChangeAnimState(EChrAnimState::StandRun);
}

void UFreezeDeBuff::ActorFreeze(float GlobalAnimRateScale)
{
	OwnerCharacter->GetMesh()->GlobalAnimRateScale = GlobalAnimRateScale;

	TArray<AActor*> ChildActors;
	OwnerCharacter->GetAllChildActors(ChildActors);

	for (AActor* Actor : ChildActors)
	{
		TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
		Actor->GetComponents(SkeletalMeshComponents);

		for (USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
		{
			if (IsValid(SkeletalMeshComponent))
				SkeletalMeshComponent->GlobalAnimRateScale = GlobalAnimRateScale;
		}
	}
}
