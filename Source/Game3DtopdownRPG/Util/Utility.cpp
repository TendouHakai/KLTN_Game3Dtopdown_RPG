// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility.h"

UUtility::UUtility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UUtility::IsEditorPlay()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}
