// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UShieldBuff::BeginBuff()
{
	Super::BeginBuff();

	float BuffAmount = 0.0f;
	if (0 < HeroBuffInfo.BuffAmount.Num())
		BuffAmount = HeroBuffInfo.BuffAmount[0];

	OwnerCharacter->SetShield(CasterCharacter->getMaxHP() * BuffAmount * 0.01f);
	OwnerCharacter->SetMaxShield(CasterCharacter->getMaxHP());
	OwnerCharacter->SetIsShieldOn(true);
}

void UShieldBuff::EndBuff(bool bForcedEnd)
{
	if (bActiveBuff == true && HasOwnerOnlyOneBuffOfThis() == true)
	{
		OwnerCharacter->SetShield(0.f);
		OwnerCharacter->SetMaxShield(0.f);
		OwnerCharacter->SetIsShieldOn(false);
	}

	Super::EndBuff(bForcedEnd);
}

void UShieldBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwnerCharacter->GetShield() <= 0.f || false == OwnerCharacter->IsCharacterAlive())
	{
		EndBuff();
	}
}

void UShieldBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	Super::RenewBuff(RenewBuffInfo);
	float BuffAmount = 0.0f;
	if (0 < HeroBuffInfo.BuffAmount.Num())
		BuffAmount = HeroBuffInfo.BuffAmount[0];

	OwnerCharacter->SetShield(CasterCharacter->getMaxHP() * BuffAmount * 0.01f);
	OwnerCharacter->SetMaxShield(CasterCharacter->getMaxHP());
	OwnerCharacter->SetIsShieldOn(true);
}
