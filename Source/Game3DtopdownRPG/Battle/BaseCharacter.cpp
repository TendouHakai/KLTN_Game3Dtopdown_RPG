// Fill out your copyright notice in the Description page of Project Settings.


#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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

