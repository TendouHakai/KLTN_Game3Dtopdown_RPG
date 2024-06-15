// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UENUM(BlueprintType)
enum class EDropState : uint8
{
	DROP,
	CHASE_PICKUP,
};

class ACoin;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoinPicked, ACoin*, PickedCoin);

UCLASS(Blueprintable, BlueprintType)
class GAME3DTOPDOWNRPG_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Coin")
	void OnCoinStartChase();

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void Emit(FVector EmitVel, FRotator RotVel);

	void SetState(EDropState state);
	void UpdateState(float DeltaSeconds);
	void StateDropping(float DeltaSeconds);
	void StateSucking(float DeltaSeconds);
	bool IsPickUp();

	UPROPERTY(BlueprintAssignable, Category = "Coin")
	FCoinPicked OnCoinPicked;

private:
	FVector velocity_;
	FRotator rot_vel_;
	EDropState state_;

	bool bRotOnDrop = true;
	float Speed = 1.0f;
	int32 BountCnt;
	UPROPERTY() APawn* TargetCharacter;
};
