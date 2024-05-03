// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "BattleBuffStateWidget.generated.h"

class ABaseCharacter;
class UBuffStateComponent;
class UBaseBuff;
class UBattleBuffInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UBattleBuffStateWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	UBattleBuffStateWidget();

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "BattleBuffStateWidget")
	void SetBattleInfoContainer(UBattleBuffInfo* BattleBuffInfo);

	UFUNCTION(BlueprintCallable, Category = "BattleBuffStateWidget")
	virtual void SetBattleCharacter(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "BattleBuffStateWidget")
	void ClearBuffStateComponentInfo();

	UFUNCTION()	virtual void UpdateBuffInfo();

protected:
	void HideBuffStateComponent(int Idx);

	void CastActorToBaseCharacter();
	virtual void SetBuffInfo();

	bool SetBuffStateComponentInfo(int Idx, UBaseBuff* BaseBuff);

	virtual int32 GetMaxBuffComponent() const { return MAX_BUFF_COMP; }

	void AttachBuffController();

protected:
	UPROPERTY() AActor* BattleActor;
	UPROPERTY()	ABaseCharacter* BattleCharacter;
	UPROPERTY() TArray<UBuffStateComponent*> BuffStateComponentArray;

	int32 PassiveBuffCount;
	//UCBattleBuffInfo* BattleBuffInfoWidget;

private:
	enum
	{
		MAX_BUFF_COMP = 10,
	};
};
