// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetMgr.h"

const TArray<FDerivedWidgetPath>& UAssetMgr::GetDerivedWidgetPaths()
{
    return DerivedWidgetPaths;
}

UClass* UAssetMgr::LoadClass(const FString& ClassPath, UClass* BaseClass, UObject* Outer)
{
    FString PathName = ClassPath;
    ConstructorHelpers::StripObjectClass(PathName, true);

	// If there is no dot, add ".<object_name>_C"
	int32 PackageDelimPos = INDEX_NONE;
	PathName.FindChar(TCHAR('.'), PackageDelimPos);
	if (PackageDelimPos == INDEX_NONE)
	{
		int32 ObjectNameStart = INDEX_NONE;
		PathName.FindLastChar(TCHAR('/'), ObjectNameStart);
		if (ObjectNameStart != INDEX_NONE)
		{
			const FString ObjectName = PathName.Mid(ObjectNameStart + 1);
			PathName += TCHAR('.');
			PathName += ObjectName;
			PathName += TCHAR('_');
			PathName += TCHAR('C');
		}
	}

	return StaticLoadClass(BaseClass, Outer, *PathName);
}

UClass* UAssetMgr::FastLoadClass(const FString& FullPath, UClass* BaseClass, UObject* Outer)
{
    return StaticLoadClass(BaseClass, Outer, *FullPath);
}
