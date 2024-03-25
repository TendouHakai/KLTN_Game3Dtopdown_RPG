// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Singleton.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API USingleton : public UObject
{
	GENERATED_BODY()
public:
	virtual void Init() {}
	virtual void Destroy() {}
	virtual void Reset() {}
	virtual void EndPlay() {}
};
