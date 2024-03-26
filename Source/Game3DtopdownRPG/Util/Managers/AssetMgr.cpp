// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetMgr.h"

const TArray<FDerivedWidgetPath>& UAssetMgr::GetDerivedWidgetPaths()
{
    return DerivedWidgetPaths;
}

UClass* UAssetMgr::FastLoadClass(const FString& FullPath, UClass* BaseClass, UObject* Outer)
{
    return StaticLoadClass(BaseClass, Outer, *FullPath);
}
