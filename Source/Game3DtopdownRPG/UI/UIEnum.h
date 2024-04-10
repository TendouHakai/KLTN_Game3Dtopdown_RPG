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

	// Battle
	BattleWidget,
	Max,
};

UENUM(BlueprintType)
enum class EUILayer : uint8
{
	None			UMETA(DisplayName = "None"),
	Scene			UMETA(DisplayName = "Scene"),
	Popup			UMETA(DisplayName = "Popup"),
	Max,
};
