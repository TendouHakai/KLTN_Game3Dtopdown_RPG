// Fill out your copyright notice in the Description page of Project Settings.


#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Buff/BuffControllerComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter() : HeroID(1), Level(1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HeroBuffController = Cast<UBuffControllerComponent>(GetComponentByClass(UBuffControllerComponent::StaticClass()));

	SkeletalMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	HitFreezer = Cast<UHitFreezer>(GetComponentByClass(UHitFreezer::StaticClass()));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SkeletalMesh->IsVisible())
	{
		GetMesh()->GlobalAnimRateScale = 0.0f;
		return;
	}

	if (GetAnimInstance() && GetAnimInstance()->IsAnimAttackState())
	{
		GetMesh()->GlobalAnimRateScale = AttackSpeedRate;
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseCharacter::GetHealthRatio()
{
	float Ratio = getHP() / getMaxHP();
	return FMath::Clamp<float>(Ratio, 0.0f, 1.0f);
}

bool ABaseCharacter::GetEnemyTeam(ECharTeam& OutEnemyTeam)
{
	bool bFindEnemyTeam = false;
	switch (CharTeam)
	{
	case ECharTeam::Ally:
		OutEnemyTeam = ECharTeam::Enemy;
		bFindEnemyTeam = true;
		break;
	case ECharTeam::Enemy:
		OutEnemyTeam = ECharTeam::Ally;
		bFindEnemyTeam = true;
		break;
	}
	return bFindEnemyTeam;
}

bool ABaseCharacter::IsCharacterDamageable()
{
	if (false == IsCharacterAlive())
		return false;

	if (false == IsValid(SkeletalMesh))
		return false;

	if (SkeletalMesh->IsVisible()) return true;

	return false;
}

void ABaseCharacter::HitFreeze(float FreezeDuration, bool bApplyColor)
{
	if (IsValid(HitFreezer))
		HitFreezer->HitFreeze(FreezeDuration, bApplyColor);
}

void ABaseCharacter::SetMovementSpeedRate(float MovementSpeed)
{
	this->MovementSpeedRate = MovementSpeed;
	
	if (GetCharacterMovement() != nullptr)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSpeedRate;
	}
}

void ABaseCharacter::StartSkillAdditionalProcess(int32 SkillIdx)
{
}

void ABaseCharacter::EndSkillAdditionalProcess()
{
}

void ABaseCharacter::AddBuffToAttacker(ABaseCharacter* Attacker, const FHeroBuffInfo& HeroBuffInfo)
{
	if (false == IsValidBuff(HeroBuffInfo))
		return;

	if (true == IsEnemyBuff(HeroBuffInfo))
		return;

	HeroBuffController->CreateBuff(Attacker, HeroBuffInfo);
}

void ABaseCharacter::AddBuffToDefender(ABaseCharacter* Attacker, const FHeroBuffInfo& HeroBuffInfo)
{
	if (false == IsCharacterAlive())
		return;

	if (false == IsValidBuff(HeroBuffInfo))
		return;

	if (false == IsEnemyBuff(HeroBuffInfo))
		return;

	HeroBuffController->CreateBuff(Attacker, HeroBuffInfo);
}

bool ABaseCharacter::IsCharacterAlive()
{
	return (GetAnimState() != EChrAnimState::Die) ? true : false;
}

void ABaseCharacter::FindHaveBuff(const UClass* ClassType, TArray<UBaseBuff*>& BuffArray)
{
	if (false == IsValid(HeroBuffController))
		return;

	HeroBuffController->FindHaveBuff(ClassType, BuffArray);
}

bool ABaseCharacter::IsValidBuff(const FHeroBuffInfo& HeroBuffInfo)
{
	return (EHeroBuffType::None_Buff <= HeroBuffInfo.BuffType) ? false : true;
}

bool ABaseCharacter::IsEnemyBuff(const FHeroBuffInfo& HeroBuffInfo)
{
	return (EBuffTargetType::Enemy == HeroBuffInfo.BuffTarget) ? true : false;
}

