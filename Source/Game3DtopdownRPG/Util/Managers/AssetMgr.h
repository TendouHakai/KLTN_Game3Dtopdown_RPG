// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "AssetMgr.generated.h"

USTRUCT()
struct FDerivedWidgetPath
{
	GENERATED_BODY()

	UPROPERTY()
	FString WidgetFullPath;

	UPROPERTY()
	int32 Layer;

	UPROPERTY()
	int32 bStayInViewport;
};

UENUM(BlueprintType)
enum class EGameTextureType : uint8
{
	None,
	Buff,
	Item,
	Max,
};

UCLASS(Config = DerivedWidgetPaths)
class GAME3DTOPDOWNRPG_API UAssetMgr : public USingleton
{
	GENERATED_BODY()

public:
	const TArray<FDerivedWidgetPath>& GetDerivedWidgetPaths();
	static UClass* LoadClass(const FString& ClassPath, UClass* BaseClass, UObject* Outer);
	static UClass* FastLoadClass(const FString& FullPath, UClass* BaseClass, UObject* Outer);

	UFUNCTION(BlueprintCallable, Category = "Asset Manager")
	UTexture2D* LoadTexture2D(const FString& Name, EGameTextureType Type = EGameTextureType::None);

private:
	UPROPERTY(Config)
	TArray<FDerivedWidgetPath> DerivedWidgetPaths;
};
