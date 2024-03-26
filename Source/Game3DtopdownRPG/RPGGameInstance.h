// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Util/Managers/AssetMgr.h"

#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	static URPGGameInstance* Instance() { return _instance; }

	UObject* GetMgrByClass(UClass* MgrClass);

private:
	template<class T>
	void CreateInstance();

	static URPGGameInstance* _instance;

	UPROPERTY()
	TMap<UObject*, USingleton*> map_mgr_;
};

#define GetSBGameInstance() URPGGameInstance::Instance()
