// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Lobby/TeleportLevel.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"
#include "BattleStruct.h"

#include "BattleClearComponent.generated.h"


UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UBattleClearComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleClearComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "BattleClearComponent")
	void SetTeleportWin(ATeleportLevel* teleport);

	UFUNCTION(BlueprintCallable, Category = "BattleClearComponent")
	void ShowTeleportWin();

	UFUNCTION(BlueprintCallable, Category = "BattleClearComponent")
	void SetBattleClearStep(EBattleClearStep step);

public:
	ATeleportLevel* TeleportWin;
	EBattleClearStep BattleClearStep;
	ABattleGameMode* BattleGameMode;
};
