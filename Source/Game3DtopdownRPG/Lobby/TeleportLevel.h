// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportLevel.generated.h"

UCLASS()
class GAME3DTOPDOWNRPG_API ATeleportLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportLevel();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetIsPlayerInRange(bool isPlayerInRange);

	UFUNCTION(BlueprintCallable)
	virtual void OnEnterLevel();
private:
	bool IsPlayerInRange = false;
};
