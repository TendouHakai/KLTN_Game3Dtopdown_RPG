// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "InstructionWidget.generated.h"

class UUIBaseButton;

UCLASS()
class GAME3DTOPDOWNRPG_API UInstructionWidget : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual bool Initialize() override;

	UFUNCTION() void OnBackBtn();

protected:
	UUIBaseButton* BackButton;
};
