// Fill out your copyright notice in the Description page of Project Settings.
#include "Game3DtopdownRPG.h"

#include "RPGGameInstance.h"

#include "Util/Managers/UIBaseMgr.h"

URPGGameInstance* URPGGameInstance::_instance = nullptr;

void URPGGameInstance::Init()
{
	Super::Init();

	_instance = this;

	CreateInstance<UAssetMgr>();
	CreateInstance<UUIBaseMgr>();
}

void URPGGameInstance::Shutdown()
{
	Super::Shutdown();
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
