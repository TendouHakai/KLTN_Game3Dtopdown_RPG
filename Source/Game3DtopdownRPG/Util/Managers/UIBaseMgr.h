// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "../../UI/UIWidget.h"
#include "../../UI/UIEnum.h"

#include "UIBaseMgr.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetData
{
	GENERATED_USTRUCT_BODY()

public:
	inline UUIWidget* GetWidget() { return IsWidgetValid() ? WidgetPtr.Get() : nullptr; }

	UUIWidget* GetOrCreateWidget();
	inline void ResetInstance() { WidgetPtr.Reset(); }

	inline bool IsWidgetValid() const { return WidgetPtr.IsValid() && !(WidgetPtr.IsStale() || WidgetPtr->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed)); }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIWidgetData")
	EUILayer Layer = EUILayer::Scene;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIWidgetData")
	uint32 bStayInViewport : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UIWidgetData")
	FString WidgetFullPath;

	uint16 WidgetId;

protected:
	UPROPERTY()
	TWeakObjectPtr<UUIWidget> WidgetPtr;
};

struct UISceneData
{
	UISceneData() { }

	uint16 WidgetId;

	// 현재 Scene이 들고 있는 Widget
	TArray<uint16> ChildWidgetIds;
};

UCLASS()
class GAME3DTOPDOWNRPG_API UUIBaseMgr : public USingleton
{
	GENERATED_BODY()
public: 
	virtual void Init() override;

	virtual void EndPlay() override;
	virtual void Tick();

	virtual void Destroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UIMgr")
	void Update();

	//UFUNCTION(BlueprintCallable, Category = "UIMgr")
	//bool GetInViewPort(EUIName UIName);

	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UIMgr")
	//bool IsCurScene(EUIName UIName);

	FUIWidgetData* GetWidgetData(UUIWidget* Widget);
	FUIWidgetData* GetWidgetData(EUIName UIName);

	UFUNCTION(BlueprintCallable, Category = "UIMgr")
	UUIWidget* GetUI(EUIName UIName);

	template<typename WidgetType>
	WidgetType* GetUI(EUIName UIName)
	{
		return GetUI<WidgetType>((uint16)UIName);
	}

	template<typename WidgetType>
	WidgetType* GetUI(uint16 WidgetId)
	{
		FUIWidgetData* WidgetData = GetWidgetData(WidgetId);
		if (WidgetData && WidgetData->IsWidgetValid())
			return Cast<WidgetType>(WidgetData->GetWidget());
		else
			return nullptr;
	}

// OPEN UI
	UFUNCTION(BlueprintCallable, Category = "UIMgr")
	UUIWidget* OpenUI(EUIName UIName, bool Immediately = false, bool bPreScene = false);

	template<typename WidgetType>
	WidgetType* OpenUI(EUIName UIName, bool Immediately = false, bool bPreScene = false)
	{
		return OpenUI<WidgetType>((uint16)UIName, Immediately, bPreScene);
	}

	template<typename WidgetType>
	WidgetType* OpenUI(uint16 WidgetId, bool Immediately = false, bool bPreScene = false)
	{
		FUIWidgetData* WidgetData = GetWidgetData(WidgetId);
		if (!WidgetData)
		{
			//UUtility::ShippingLog(FString::Printf(TEXT("None WidgetDatas UIName[%d]"), (int32)WidgetId));
			return nullptr;
		}

		WidgetType* Widget = Cast<WidgetType>(WidgetData->GetOrCreateWidget());
		if (!IsValid(Widget))
		{
			//UUtility::ShippingLog(FString::Printf(TEXT("None Widget UIName[%d]"), (int32)WidgetId));
			return nullptr;
		}
		Widget->SetWidgetId(WidgetId);
		//Widget->Init(CurGameMode);

		_OpenUI(Widget, WidgetData, Immediately, bPreScene);
		return Widget;
	}

	//UFUNCTION(BlueprintCallable, Category = "UIMgr")
	//bool CloseUI(EUIName UIName, bool Immediately = false, bool isRemoveStack = true);
	//bool CloseUI(UUIWidget* Widget, bool bImmediately = false, bool bRemoveStack = true);

	//UFUNCTION(BlueprintCallable, Category = "UIMgr")
	//bool CloseWidget(UUIWidget* Widget, bool bImmediately = false, bool bRemoveStack = true);

// OPEN SCENE
	UFUNCTION(BlueprintCallable, Category = "UIMgr")
	UUIWidget* OpenScene(EUIName SceneName);

	template<typename WidgetType>
	WidgetType* OpenScene(EUIName SceneName, bool NeedRestore = true)
	{
		return OpenScene<WidgetType>((uint16)SceneName, NeedRestore);
	}

	template<typename WidgetType>
	WidgetType* OpenScene(uint16 WidgetId, bool NeedRestore = true) 
	{
		UISceneData* CurSceneData = GetSceneData(WidgetId);
		if (!CurSceneData)
			return nullptr;

		CurSceneId = WidgetId;

		// xữ lý childwidgets 

		ScenesStack.Push(CurSceneId);
		OpenUI<WidgetType>(CurSceneData->WidgetId, true);

		return GetUI<WidgetType>(CurSceneData->WidgetId);
	}

	//UFUNCTION(BlueprintCallable, Category = "UIMgr")
	//void CloseScene(bool bBackButton = false);
protected:
	void _OpenUI(class UUIWidget* Widget, FUIWidgetData* WidgetData, bool Immediately = false, bool bPreScene = false);

	FUIWidgetData* GetWidgetData(uint16 WidgetId);
	UISceneData* GetSceneData(uint16 WidgetId);

	/*UPROPERTY()
	TArray<class UCUIMsgBoxBase*> MsgBoxStack;*/

	uint16 CurSceneId;
	TArray<uint16> ScenesStack;

	//UPROPERTY()
	//UCWaitingWidget* WaitingWidget;

	UPROPERTY()
	TMap<uint16, FUIWidgetData> WidgetDatas;
	TMap<uint16, UISceneData> SceneDatas;

	//DECLARE_DELEGATE(FOnEndCloseCallBack);
	//TMap<uint16, TMap<uint16, FOnEndCloseCallBack>> OnEndCloseCallBacks;

	//UPROPERTY()
	//TSet<uint16> ActivityWidgetIdStoreSet;

	//TArray<FMsgBoxInfo> MsgBoxInfos;
	bool bActive = false;
};
