// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Game3DtopdownRPG/Define/BuildingStruct.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "InternalWidget.generated.h"


UCLASS()
class GAME3DTOPDOWNRPG_API UInternalWidget : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	UFUNCTION(BlueprintCallable)
	void SetCurrentBuilding(EBuildingType type);

	UFUNCTION(BlueprintCallable)
	void OnTapBtnMenu(int Index);

	UFUNCTION(BlueprintCallable)
	void OnTapClose();

protected:
	EBuildingType m_CurrentBuilding;
	TArray<UHorizontalBox*> ListMenu;
	UTextBlock* textNameBuilding;
};
