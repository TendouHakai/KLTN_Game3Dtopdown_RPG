// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API ALoginGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
