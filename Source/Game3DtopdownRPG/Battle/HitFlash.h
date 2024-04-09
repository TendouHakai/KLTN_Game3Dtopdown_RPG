// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitFlash.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME3DTOPDOWNRPG_API UHitFlash : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHitFlash();

	UFUNCTION(BlueprintCallable, Category = "HitFlash")
	void Flash(const FLinearColor& EmissiveColor, float FlashTime);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> DynamicMats;
	TArray<FLinearColor> OriginEmissiveColors;
	FTimerHandle BackTimer;

	FName HitFlashColorPramName = FName(TEXT("EmissiveColor"));

	void BackToOriginColor();
};
