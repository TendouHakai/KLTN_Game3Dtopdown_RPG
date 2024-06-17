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

UTexture2D* UAssetMgr::LoadTexture2D(const FString& Name, EGameTextureType Type)
{
	if (Name.IsEmpty()) return nullptr;

	FString filePath = "/Game/UI/Texture/";
	FString imagePath = "";
	switch (Type)
	{
	case EGameTextureType::None:
		break;
	case EGameTextureType::Buff:
		imagePath = "Buff/";
		break;
	case EGameTextureType::Item:
		imagePath = "Item/";
		break;
	case EGameTextureType::ItemEquipment:
		imagePath = "Item/Equipment/";
		break;
	case EGameTextureType::Skill:
		imagePath = "Skill/";
		break;
	case EGameTextureType::Max:
		break;
	default:
		break;
	}

	filePath += imagePath;
	filePath += (Name+"."+Name);
	
	//filePath = "/Game/UI/Texture/Buff/Buff_10008.Buff_10008";

	UTexture2D* tex = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(filePath)));

	return tex;
}

UTexture2D* UAssetMgr::LoadTexture2DFromPath(const FString& PathName)
{
	if (PathName.IsEmpty()) return nullptr;

	UTexture2D* tex = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(PathName)));

	if (nullptr == tex) return nullptr;
	return tex;
}
