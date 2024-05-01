// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffStruct.h"
#include "BaseBuffActor.generated.h"

class ABaseCharacter;
class UBaseBuff;

UCLASS()
class GAME3DTOPDOWNRPG_API ABaseBuffActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBuffActor();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitBuffStateActor(ABaseCharacter* InOwner, UBaseBuff* BaseBuff);

	UFUNCTION(BlueprintImplementableEvent, Category = "BuffStateActor")
	void InitBuffStateActorBP();

	virtual void ShowBuffStateActor() {}
	virtual void HideBuffStateActor() {}
	virtual void EndBuffStateActor();

	virtual EBuffActorType GetBuffActorType();
public:
	void AddBuffInfo(UBaseBuff* BaseBuff);
	void RemoveBuffInfo(UBaseBuff* BaseBuff);

protected:
	void AddBuffParticleSystem(UBaseBuff* BaseBuff);
	UParticleSystemComponent* CreateParticleSystemComponent(UBaseBuff* BaseBuff);
	UParticleSystem* CreateBuffEffectParticle(UBaseBuff* BaseBuff);
	FName GetParticleAttachBoneName(int32 BuffParticleIdx, FName BoneName);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ABaseCharacter* OwnerCharacter;
	UPROPERTY() TMap<UBaseBuff*, UParticleSystemComponent*> BuffParticleSystems;

};
