// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
class ABaseGameMode;
class UUIBaseMgr;

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
	virtual void Destroy(UUIBaseMgr* InUIManager);

	UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	virtual void Update();

protected:
	template<class T>
	T* GetOwnUI(const FString& InWidgetName, bool bValidCheck = true)
	{
		T* Widget = Cast<T>(GetWidgetFromName(FName(*InWidgetName)));
		if (!Widget)
		{
			//UUtility::ShippingLog(FString::Printf(TEXT("GetWidget Failed[%s] WidgetName[%s] bValidCheckOption[%s]"), *InWidgetName, *GetName(), bValidCheck ? TEXT("true") : TEXT("false")));
			if (bValidCheck)
				bValidWidget = false;
		}
		return Widget;
	}


	bool bValidWidget;
};
