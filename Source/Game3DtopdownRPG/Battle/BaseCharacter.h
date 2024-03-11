// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GAME3DTOPDOWNRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float value) {
		if (value != 0) {
			FVector forwardV = FVector(0, -1, 0);
			AddMovementInput(value * forwardV);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float value) {
		if (value != 0) {
			FVector rightV = FVector(1, 0, 0);
			AddMovementInput(value * rightV);
		}
	}
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
