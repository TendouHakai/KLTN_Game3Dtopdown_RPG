// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGetter.h"
#include "RPGGameInstance.h"
#include "Kismet/GameplayStatics.h"

UObject* GetMgrFunc(UClass* MgrClass)
{
	return URPGGameInstance::Instance()->GetMgrByClass(MgrClass);
}

AGameMode* GetGameModeAsFunc()
{
	return (AGameMode*)UGameplayStatics::GetGameMode(GetRPGGameInstance());
}
