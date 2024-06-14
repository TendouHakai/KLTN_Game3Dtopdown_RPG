// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffStruct.h"
#include "BuffControllerComponent.generated.h"

class ABaseCharacter;
class UBaseBuff;
class ABuffStateActor;
class ABaseBuffActor;

UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UBuffControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffControllerComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostLoad() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	UBaseBuff* CreateBuff(ABaseCharacter* Caster, const FHeroBuffInfo& HeroBuffInfo, bool bAllowedDuplicate = false);

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void DestroyBuff(UBaseBuff* BaseBuff);

	template<class T>
	void BindUpdateBuffInfoCallback(T* Owner)
	{
		UpdateBuffInfoCallBack.Unbind();
		UpdateBuffInfoCallBack.BindDynamic(Owner, &T::UpdateBuffInfo);
	}

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	UBaseBuff* FindSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& HeroPassiveBuff);

	void RenewBuff(UBaseBuff* const BaseBuff, const FHeroBuffInfo& HeroBuffInfo);

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void DeleteBuffCheck();

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void FindHaveBuff(const UClass* ClassType, TArray<UBaseBuff*>& BuffArray);

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void ClearBuffStateActor();

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void ShowBuffEffects();

	UFUNCTION(BlueprintCallable, Category = "BuffController")
	void HideBuffEffects();

private:
	void UpdateBuffInfo();
	void TickBuff(float DeltaTime);

	bool IsNecessaryBuffActor(UBaseBuff* CheckBuff);

protected:
	UBaseBuff* CreateBuff_Implementation(ABaseCharacter* Caster, const FHeroBuffInfo& HeroBuffInfo, bool bAllowedDuplicate = false);
	UBaseBuff* CreateInstance(const EHeroBuffType& type, const FHeroBuffInfo& HeroBuffInfo);

	ABaseBuffActor* SpawnBuffActor(EBuffActorType BuffActorType, UBaseBuff* BaseBuff);
	void DestroyBuffStateActor(ABaseBuffActor* BaseBuffActor);

	bool IsBuffCreateException(const FHeroBuffInfo& HeroBuffInfo);
	bool IsNegativeBuff(const FHeroBuffInfo& HeroBuffInfo);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ABaseCharacter* OwnerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	TArray<UBaseBuff*> HeroBuffArray;

private:
	UPROPERTY()	TArray<UBaseBuff*> DeleteHeroBuffArray;

private:
	DECLARE_DYNAMIC_DELEGATE(FUpdateBuffInfo);
	FUpdateBuffInfo UpdateBuffInfoCallBack;

	UPROPERTY()	ABuffStateActor* BuffStateActor;

	TArray<EHeroBuffType> debuffArray = { EHeroBuffType::Flame, EHeroBuffType::Bleeding, EHeroBuffType::Blindness,
		EHeroBuffType::Damage_Decrease, EHeroBuffType::Freezing, EHeroBuffType::HealBan, EHeroBuffType::Silence, EHeroBuffType::Slow, EHeroBuffType::Stun };
};
