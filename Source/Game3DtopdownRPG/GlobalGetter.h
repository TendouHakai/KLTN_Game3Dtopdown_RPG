// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// GetMgr
UObject* GetMgrFunc(UClass* MgrClass);
#define GetMgr(MgrClass) Cast<MgrClass>(GetMgrFunc(MgrClass::StaticClass()))
