// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utility.generated.h"
/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUtility: public UObject
{
public:
	GENERATED_UCLASS_BODY()


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static bool IsEditorPlay();
};
