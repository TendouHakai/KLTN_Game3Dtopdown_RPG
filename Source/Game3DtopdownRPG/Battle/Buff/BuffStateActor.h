// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuffActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "BuffStateActor.generated.h"


UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API ABuffStateActor : public ABaseBuffActor
{
	GENERATED_BODY()

public:	
	ABuffStateActor();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void ShowBuffStateActor() override;
	virtual void HideBuffStateActor() override;
	virtual void EndBuffStateActor() override;

	void ResetParticles();
	virtual EBuffActorType GetBuffActorType() override;

protected:
	TArray<UTexture2D*> ShowingBuffTextures;

private:
	bool bBuffTextPlay = false;
	int32 BuffTextPlayIdx = 0;

	float BuffTextEffectPlayWaitTime = 0.f;
	const float EffectPlayWaitTerm = 0.6f;

	int32 m_PlayerCharacterHeroReckey = 0;

};
