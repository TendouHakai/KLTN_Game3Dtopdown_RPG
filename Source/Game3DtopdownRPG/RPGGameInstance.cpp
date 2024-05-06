// Fill out your copyright notice in the Description page of Project Settings.
#include "RPGGameInstance.h"

#include "Game3DtopdownRPG.h"
#include "Util/Managers/UIBaseMgr.h"
#include "Util/Managers/TableMgr.h"
#include "Util/Managers/HeroBuffMgr.h"
#include "Util/Managers/ItemMgr.h"

URPGGameInstance* URPGGameInstance::_instance = nullptr;

void URPGGameInstance::Init()
{
	Super::Init();

	_instance = this;

	CreateInstance<UAssetMgr>();
	CreateInstance<UUIBaseMgr>();
	CreateInstance<UTableMgr>();
	CreateInstance<UHeroBuffMgr>();
	CreateInstance<UItemMgr>();
}

void URPGGameInstance::Shutdown()
{
	Super::Shutdown();

	for (auto& entry : map_mgr_) {
		entry.Value->Destroy();
		entry.Value = nullptr;
	}
	map_mgr_.Empty();

	_instance = nullptr;
}

UObject* URPGGameInstance::GetMgrByClass(UClass* MgrClass)
{
	if (!_instance)
		return nullptr;

	if (USingleton** val = map_mgr_.Find(MgrClass))
	{
		return *val;
	}

	return nullptr;
}

void URPGGameInstance::EndPlayMgr()
{
	for (auto& entry : map_mgr_) {
		entry.Value->EndPlay();
	}
}

template<class T>
void URPGGameInstance::CreateInstance()
{
	if (map_mgr_.Contains(T::StaticClass())) {
		ensureMsgf(false, TEXT("CreateInstance[%s] already key exist."), *T::StaticClass()->GetName());
		return;
	}

	T* obj = NewObject<T>();
	obj->Init();
	map_mgr_.Add(T::StaticClass(), obj);
}
