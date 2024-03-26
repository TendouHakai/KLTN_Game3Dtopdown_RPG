// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGetter.h"
#include "RPGGameInstance.h"

UObject* GetMgrFunc(UClass* MgrClass)
{
	return URPGGameInstance::Instance()->GetMgrByClass(MgrClass);
}
