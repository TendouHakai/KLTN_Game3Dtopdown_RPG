#pragma once
#include "UIEnum.generated.h"

// is a widgetID in UIbaseMgr
UENUM(BlueprintType)
enum class EUIName : uint8
{
	None = 0,
	// Page 
	LoginPage,
	SettingMenu,
	LoadingWidget,

	// Battle
	BattleWidget,
	BattleBossProgessWidget,
	BattleFailWidget,
	BattleVictoryWidget,

	// Inventory
	InventoryPage,
	InventoryEquipmentPage,
	InventoryItemSellPopup,

	// Equipment
	HeroEquipmentPage,

	// MsgBox
	MsgBoxBasic,
	MsgBoxReward,

	// Lobby
	InternalPage,
	ForgingItemEquipmentPage,
	UpgradeItemEquipmentPage,
	MakingPotionPage,
	RuneBuffPage,
	BattleStagePage,
	SelectBuffPage,

	Max,
};

UENUM(BlueprintType)
enum class EUILayer : uint8
{
	None			UMETA(DisplayName = "None"),
	Scene			UMETA(DisplayName = "Scene"),
	Popup			UMETA(DisplayName = "Popup"),
	MsgBox			UMETA(DisplayName = "MsgBox"),
	Max,
};
