// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UBaseWidget(const FObjectInitializer& objectInitializer);

	virtual bool Initialize() override;
	virtual void Init();	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	bool bValidWidget;
};
