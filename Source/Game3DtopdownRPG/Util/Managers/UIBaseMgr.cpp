// Fill out your copyright notice in the Description page of Project Settings.
#include "UIBaseMgr.h"

#include "Game3DtopdownRPG/Game3DtopdownRPG.h"

#include "AssetMgr.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"
#include "Game3DtopdownRPG/UI/MsgBox/UIBaseMsgBox.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxBasic.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"

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

void UUIBaseMgr::Init(ABaseGameMode* InGameMode)
{
	this->CurGameMode = InGameMode;
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
	if (CurSceneId == 0) return;

	UISceneData* CurSceneData = GetSceneData(CurSceneId);
	if (!CurSceneData) return;

	for (uint16 ChildWidgetId : CurSceneData->ChildWidgetIds)
	{
		FUIWidgetData* StackedWidgetData = GetWidgetData(ChildWidgetId);
		if (!StackedWidgetData || !StackedWidgetData->IsWidgetValid()) continue;

		StackedWidgetData->GetWidget()->Update();
	}
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

bool UUIBaseMgr::CloseUI(EUIName UIName, bool Immediately /*= false*/, bool isRemoveStack /*= true*/)
{
	return CloseUI((uint16)UIName, Immediately, isRemoveStack);
}

bool UUIBaseMgr::CloseUI(UUIWidget* Widget, bool bImmediately /*= false*/, bool bRemoveStack /*= true*/)
{
	return CloseUI(Widget->GetWidgetId(), bImmediately, bRemoveStack);
}

bool UUIBaseMgr::CloseUI(uint16 WidgetId, bool Immediately /*= false*/, bool isRemoveStack /*= true*/)
{
	UUIWidget* Widget = GetUI<UUIWidget>(WidgetId);
	if (nullptr == Widget)
	{
		return false;
	}

	Widget->OnClose(Immediately);

	if (true == isRemoveStack)
	{
		UISceneData* CurSceneData = GetSceneData(CurSceneId);
		if (CurSceneData)
		{
			CurSceneData->ChildWidgetIds.Remove(WidgetId);
		}
	}

	return true;
}

bool UUIBaseMgr::CloseWidget(UUIWidget* Widget, bool bImmediately /*= false*/, bool bRemoveStack /*= true*/)
{
	return CloseUI(Widget, bImmediately, bRemoveStack);
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

void UUIBaseMgr::CloseScene(bool bBackButton /*= false*/)
{
	CloseScene(CurSceneId, true, bBackButton);
}

void UUIBaseMgr::CloseScene(uint16 WidgetId, bool bStack /*= false*/, bool bBackButton /*= false*/)
{
	auto CurSceneData = GetSceneData(WidgetId);
	if (!CurSceneData)
		return;

	for (int32 i = 0; i < CurSceneData->ChildWidgetIds.Num(); ++i)
	{
		FUIWidgetData* UIWidgetData = WidgetDatas.Find(CurSceneData->ChildWidgetIds[i]);
		if (UIWidgetData && UIWidgetData->IsWidgetValid())
		{
			if (bStack)
				CloseUI(UIWidgetData->WidgetId, true, false);
		}
	}

	if (bStack)
		CurSceneData->ChildWidgetIds.Empty();

	if (bStack)
	{
		if (0 < ScenesStack.Num())
		{
			ScenesStack.Pop();
			if (ScenesStack.Num() > 0)
			{
				OpenScene<UUIWidget>(ScenesStack.Top());
			}
		}
	}
}

void UUIBaseMgr::CloseAllUI()
{
	for (auto& WidgetPair : WidgetDatas)
	{
		FUIWidgetData& UIWidgetData = WidgetPair.Value;

		if (UIWidgetData.IsWidgetValid())
		{
			UUIWidget* UIWidget = UIWidgetData.GetWidget();

			//UE_LOG(LogClass, Warning, TEXT("CloseAllUI(%s)"), *UIWidget->GetName());
			if(UIWidgetData.WidgetId == (uint8)EUIName::LoadingWidget)
				continue;

			UIWidget->RemoveFromParent();
			UIWidgetData.ResetInstance();
		}
	}

	for (auto& kv : SceneDatas)
	{
		kv.Value.ChildWidgetIds.Empty();
	}

	ScenesStack.Empty();
	CurSceneId = INVALID_WIDGET_ID;
}

class UUIBaseMsgBox* UUIBaseMgr::OpenMsgBox(EUIMsgBoxType MsgBoxType, const FString& Desc, EUIMsgBoxBtnType BtnType /*= EUIMsgBoxBtnType::Confirm*/,
	UObject* Owner /*= nullptr*/, const FName& LeftTapFunctionName /*= TEXT("")*/, const FName& RightTapFunctionName /*= TEXT("")*/, 
	const FString& LeftBtnText /*= TEXT("")*/, const FString& RightBtnText /*= TEXT("")*/, bool bAddWaitMsgBoxStack /*= true*/, bool bIsDisableBackBtnExit /*= false*/)
{
	if (5 < MsgBoxStack.Num())
	{
		return nullptr;
	}

	uint16 UIName = (uint16)EUIName::None;
	switch (MsgBoxType)
	{
	case EUIMsgBoxType::None:
		return nullptr;
	case EUIMsgBoxType::Basic:
		UIName = (uint16)EUIName::MsgBoxBasic;
		break;
	case EUIMsgBoxType::Reward:
		UIName = (uint16)EUIName::MsgBoxReward;
		break;
	default:
		return nullptr;
	}

	auto* WidgetData = GetWidgetData(UIName);
	if (!WidgetData)
	{
		return nullptr;
	}

	UClass* LoadClass = GetMgr(UAssetMgr)->FastLoadClass(WidgetData->WidgetFullPath, UUIWidget::StaticClass(), GetRPGGameInstance());
	UUIBaseMsgBox* MsgBox = CreateWidget<UUIBaseMsgBox>(GetRPGGameInstance(), LoadClass);
	if (!MsgBox)
	{
		return nullptr;
	}

	MsgBox->SetWidgetId(/*(uint16)*/UIName);
	MsgBox->Init(CurGameMode);
	MsgBox->AddToViewport((int32)WidgetData->Layer);
	MsgBox->SetMsgBoxType(MsgBoxType);
	MsgBox->SetDesc(Desc);
	if (EUIMsgBoxType::Basic == MsgBoxType)
	{
		UMsgBoxBasic* MsgBoxBasic = Cast<UMsgBoxBasic>(MsgBox);
		if (nullptr != MsgBoxBasic)
		{
			MsgBoxBasic->SetButtonType(BtnType);
			if (!LeftTapFunctionName.IsNone()) MsgBoxBasic->AddHandler(EMsgEventButtonType::Left, Owner, LeftTapFunctionName);
			if (!RightTapFunctionName.IsNone()) MsgBoxBasic->AddHandler(EMsgEventButtonType::Right, Owner, RightTapFunctionName);
		}
	}
	else if (EUIMsgBoxType::Reward == MsgBoxType)
	{
		UMsgBoxReward* MsgBoxReward = Cast<UMsgBoxReward>(MsgBox);
		if (nullptr != MsgBoxReward)
		{
			MsgBoxReward->SetButtonType(BtnType);
			if (!LeftTapFunctionName.IsNone()) MsgBoxReward->AddHandler(EMsgEventButtonType::Left, Owner, LeftTapFunctionName);
			if (!RightTapFunctionName.IsNone()) MsgBoxReward->AddHandler(EMsgEventButtonType::Right, Owner, RightTapFunctionName);
		}
	}

	return MsgBox;
}

void UUIBaseMgr::CloseMsgBox(FString Name)
{
	if (MsgBoxStack.Num() == 0)
	{
		return;
	}

	//CleanUp
	MsgBoxStack.RemoveAll([](UUIBaseMsgBox* MsgBox)
		{
			return !IsValid(MsgBox);
		});

	for (int32 i = MsgBoxStack.Num() - 1; 0 <= i; --i)
	{
		if (MsgBoxStack[i]->GetName() == Name)
		{
			MsgBoxStack[i]->RemoveFromParent();
			//MsgBoxStack[i]->RemoveFromViewport();
			MsgBoxStack.RemoveAt(i);
			break;
		}
	}
}

void UUIBaseMgr::CloseAllMsgBox()
{
	if (MsgBoxStack.Num() == 0)
	{
		return;
	}

	MsgBoxStack.RemoveAll([](UUIBaseMsgBox* MsgBox)
		{
			return !IsValid(MsgBox);
		});

	for (int32 i = MsgBoxStack.Num() - 1; 0 <= i; --i)
	{
		MsgBoxStack[i]->RemoveFromParent();
		//MsgBoxStack[i]->RemoveFromViewport();
		MsgBoxStack.RemoveAt(i);
		break;
	}

	MsgBoxStack.Empty();
}

void UUIBaseMgr::_OpenUI(UUIWidget* Widget, FUIWidgetData* WidgetData, bool Immediately, bool bPreScene)
{
	if (!WidgetData->bStayInViewport)
	{
		auto CurSceneData = GetSceneData(CurSceneId);
		if (!CurSceneData)
		{
			ensureMsgf(false, TEXT("UUIBaseMgr::_OpenUI CurScene = nullpointerexception"));
			return;
		}

		if (!CurSceneData->ChildWidgetIds.Contains(WidgetData->WidgetId))
		{
			if (0 < CurSceneData->ChildWidgetIds.Num())
			{
				uint16 ChildWidgetId = CurSceneData->ChildWidgetIds.Last();

				/*if (UUIWidget* PreWidget = GetUI<UUIWidget>(ChildWidgetId))
					PreWidget->OnCoveredUI();*/
			}

			CurSceneData->ChildWidgetIds.Add(WidgetData->WidgetId);
		}
	}

	Widget->AddToViewport((int32)WidgetData->Layer);
	Widget->OnOpen(Immediately);

	if (WidgetData->WidgetId == (uint8)EUIName::LoadingWidget)
	{
		LoadingWidget = Cast<ULoadingWidget>(Widget);
	}
}

UUIWidget* FUIWidgetData::GetOrCreateWidget()
{
	if (!IsWidgetValid())
	{
		UClass* LoadClass = GetMgr(UAssetMgr)->FastLoadClass(WidgetFullPath, UUIWidget::StaticClass(), GetRPGGameInstance());
		WidgetPtr = CreateWidget<UUIWidget>(GetRPGGameInstance(), LoadClass);
	}
	return GetWidget();
}
