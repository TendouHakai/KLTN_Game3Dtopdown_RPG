// Fill out your copyright notice in the Description page of Project Settings.


#include "StunDebuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UStunDebuff::BeginBuff()
{
	Super::BeginBuff();

	OwnerCharacter->BeginStun();
	OwnerCharacter->PlayStunStartSound();
}

void UStunDebuff::EndBuff(bool bForcedEnd)
{
	if (bActiveBuff == true && HasOwnerOnlyOneBuffOfThis() == true)
	{
		if (OwnerCharacter->IsCharacterAlive()/* && OwnerCharacter->IsActive()*/)
			OwnerCharacter->EndStun();
	}

	Super::EndBuff(bForcedEnd);
}
