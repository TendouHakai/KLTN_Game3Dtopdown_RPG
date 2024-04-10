// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
class UUIBaseMgr;

UCLASS()
class GAME3DTOPDOWNRPG_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public: 
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void InitInitialUI();

	UFUNCTION() void OpenReservedLevel(const FName NameLevel, const FString Options);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUIBaseMgr* UIMgr;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI Manager")
	void OnInitInitialUI();
};
