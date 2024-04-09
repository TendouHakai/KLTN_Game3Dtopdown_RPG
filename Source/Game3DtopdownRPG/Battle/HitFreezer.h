// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitFreezer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME3DTOPDOWNRPG_API UHitFreezer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHitFreezer();

	UFUNCTION(BlueprintCallable, Category = "HitFreezer")
	void HitFreeze(float FreezeDuration, bool bApplyColor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor HitFreezeColor = FLinearColor(0.755f, 0.75f, 0.75f);
protected:
	virtual void BeginPlay() override;

private:
	void EndHitFreeze();
	void SetActorGlobalAnimRateScale(float GlobalAnimRateScale);
	void SetChildActorGlobalAnimRateScale(float GlobalAnimRateScale);

	FTimerHandle EndHitFreezeTimer;
	float HitFreezeAnimRateScale = 0.001f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
