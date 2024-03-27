// Fill out your copyright notice in the Description page of Project Settings.
#include "UIBaseMgr.h"

#include "Game3DtopdownRPG/Game3DtopdownRPG.h"

#include "AssetMgr.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"

void InitWidgetData(const TArray<FDerivedWidgetPath>& DerivedWidgetPaths,
	TMap<uint16, FUIWidgetData>& WidgetDatas,
	TMap<uint16, UISceneData>& SceneDatas,
	uint16 FirstUIId)
{
	for (const FDerivedWidgetPath& DerivedWidgetPath : DerivedWidgetPaths)
	{
		FUIWidgetData UIWidgetData;
		UIWidgetData.Layer = (EUILayer)DerivedWidgetPath.Layer;
		UIWidgetData.bStayInViewport = DerivedWidgetPath.bStayInViewport;
		UIWidgetData.WidgetId = FirstUIId++;
		UIWidgetData.WidgetFullPath = DerivedWidgetPath.WidgetFullPath;
		WidgetDatas.Add(UIWidgetData.WidgetId, UIWidgetData);

		// Scene Layer ¼¼ÆÃ
		if (UIWidgetData.Layer == EUILayer::Scene)
		{
			UISceneData SceneData;
			SceneData.WidgetId = UIWidgetData.WidgetId;
			SceneData.ChildWidgetIds.Empty();
			SceneDatas.Add(SceneData.WidgetId, SceneData);
		}
	}
}

void UUIBaseMgr::Init()
{
	Super::Init();
	InitWidgetData(GetMgr(UAssetMgr)->GetDerivedWidgetPaths(), WidgetDatas, SceneDatas, 1);
}

void UUIBaseMgr::EndPlay()
{
	Super::EndPlay();
}

void UUIBaseMgr::Tick()
{

}

void UUIBaseMgr::Destroy()
{
	Super::Destroy();
}

void UUIBaseMgr::Update()
{
}

FUIWidgetData* UUIBaseMgr::GetWidgetData(UUIWidget* Widget)
{
	return GetWidgetData(Widget->GetWidgetId());
}

FUIWidgetData* UUIBaseMgr::GetWidgetData(EUIName UIName)
{
	return GetWidgetData((uint16)UIName);
}

UUIWidget* UUIBaseMgr::OpenUI(EUIName UIName, bool Immediately, bool bPreScene)
{
	return OpenUI<UUIWidget>(UIName, Immediately, bPreScene);;
}

UUIWidget* UUIBaseMgr::GetUI(EUIName UIName)
{
	return GetUI<UUIWidget>(UIName);
}

FUIWidgetData* UUIBaseMgr::GetWidgetData(uint16 WidgetId)
{
	return WidgetDatas.Find(WidgetId);
}

UISceneData* UUIBaseMgr::GetSceneData(uint16 WidgetId)
{
	return SceneDatas.Find(WidgetId);
}

UUIWidget* UUIBaseMgr::OpenScene(EUIName SceneName)
{
	return OpenScene<UUIWidget>(SceneName);
}

void UUIBaseMgr::_OpenUI(UUIWidget* Widget, FUIWidgetData* WidgetData, bool Immediately, bool bPreScene)
{
	Widget->AddToViewport((int32)WidgetData->Layer);
}

UUIWidget* FUIWidgetData::GetOrCreateWidget()
{
	if (!IsWidgetValid())
	{
		UClass* LoadClass = GetMgr(UAssetMgr)->FastLoadClass(WidgetFullPath, UUIWidget::StaticClass(), GetSBGameInstance());
		WidgetPtr = CreateWidget<UUIWidget>(GetSBGameInstance(), LoadClass);
	}
	return GetWidget();
}
