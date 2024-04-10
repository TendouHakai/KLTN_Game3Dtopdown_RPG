// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CheatableController.generated.h"

/**
 * 
 */


UCLASS()
class GAME3DTOPDOWNRPG_API ACheatableController : public APlayerController
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAdditionProc);

	UPROPERTY(BlueprintAssignable)
	FAdditionProc AdditionProc_Delegate;

	UFUNCTION(BlueprintCallable)
	void ExcuteAdditionProcDelegate();
};
	