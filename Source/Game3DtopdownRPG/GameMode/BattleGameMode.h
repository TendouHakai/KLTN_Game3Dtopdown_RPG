// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API ABattleGameMode : public ABaseGameMode
{
	GENERATED_BODY()
	
public:
	ABattleGameMode();
	virtual ~ABattleGameMode();

	virtual void InitGame(const FString& map_name, const FString& options, FString& error_message) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RepeatBattle();

	UFUNCTION(BlueprintCallable)
	void BackToStartZone();

	UFUNCTION(BlueprintCallable)
	void BackToMainMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "BattleGameMode") void OnBeginProduction();

protected:
	EBattleGameModeState GameModeState;

};
