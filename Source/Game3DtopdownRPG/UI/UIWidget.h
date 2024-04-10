// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUIWidget : public UBaseWidget
{
	GENERATED_BODY()

	friend class UUIBaseMgr;
public:
	virtual void Init() override;
	virtual void Init(ABaseGameMode* InGameMode);
	virtual void NativeConstruct() override;
	virtual void Destroy(UUIBaseMgr* InUIManager);

	void SetWidgetId(uint16 InWidgetId) { WidgetId = InWidgetId; }
	uint16 GetWidgetId() { return WidgetId;}

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnOpenBP();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnCloseBP();

	virtual void OnOpen(bool Immediately = false);
	virtual void OnClose(bool Immediately = false);
protected:
	uint16 WidgetId;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUIBaseMgr* UIMgr = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ABaseGameMode* GameMode = nullptr;
};
