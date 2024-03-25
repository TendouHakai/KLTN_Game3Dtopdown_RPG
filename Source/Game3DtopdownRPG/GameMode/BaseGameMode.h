// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public: 
	virtual void BeginPlay() override;
	virtual void InitInitialUI();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI Manager")
	void OnInitInitialUI();
};
