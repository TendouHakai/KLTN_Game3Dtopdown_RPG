// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "BattleWidget.generated.h"

class UItemSlotWidget;
class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UBattleWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void Update() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetHeroCharacter(ABaseCharacter* hero);

protected:
	void UpdateNormalEquipmentSlots();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ABaseCharacter* character;

protected:
	// UI
	TArray<UItemSlotWidget*> slots;
};
