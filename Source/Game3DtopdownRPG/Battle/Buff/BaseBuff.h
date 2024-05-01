// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffStruct.h"

#include "BaseBuff.generated.h"

class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UBaseBuff : public UObject
{
	GENERATED_BODY()

public:
	UBaseBuff();

	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo);
	virtual void BeginBuff();
	virtual void EndBuff(bool bForcedEnd = false);
	virtual void TimeEndFunction();
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo);

	virtual void Tick(float DeltaTime);
	virtual bool IsSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo);

	template<typename T>
	void BindCallBackFunc(T* audience, void (T::* InFunc)(UBaseBuff*))
	{
		OnEndBuffCallBack.RemoveAll(audience);
		OnEndBuffCallBack.AddUObject(audience, InFunc);
	}

	template<class T>
	void BindUpdateBuffInfoCallback(T* Owner, void (T::* InFunc)(UBaseBuff*))
	{
		UpdateBuffInfoCallBack.Unbind();
		UpdateBuffInfoCallBack.BindUObject(Owner, InFunc);
	}

	void SetOwnerCharacter(ABaseCharacter* Owner) { OwnerCharacter = Owner; }
	void SetDuplicated(bool Duplicated) { bDuplicated = Duplicated; }
	bool IsDuplicated() { return bDuplicated; }
	virtual const int32 GetRemainTime();

	FORCEINLINE virtual const float GetDuration() { return Duration; }
	FORCEINLINE virtual const float GetElapseTime() { return ElapseTime; }

	bool IsNecessaryBuffActor();
	virtual EBuffActorType GetSpawnActorType() { return EBuffActorType::eBuffStateActor; }
	virtual bool IsPassiveBuff() { return bIsPassiveBuff; }
	virtual int32 BuffStateIndex() { return -1; }
	virtual FName GetAttachedBoneName() { return HeroBuffInfo.AttachedBoneName; }

protected:
	void SetBuffInfoText();
	void UpdateBuffInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsPassiveBuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ElapseTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CurrentStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MaxStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FHeroBuffInfo HeroBuffInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<ABaseCharacter*> TeamBuffCharacters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ABaseCharacter* OwnerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ABaseCharacter* CasterCharacter;

protected:
	bool bActiveBuff;

private:
	bool bDuplicated;
	FString BuffInfoText;

private:
	const float OneSecond = 1.f;

	DECLARE_DELEGATE_OneParam(FUpdateBuffInfo, UBaseBuff*);
	FUpdateBuffInfo UpdateBuffInfoCallBack;
	float OneSecondElapseTime;

private:
	DECLARE_MULTICAST_DELEGATE_OneParam(FEndBuffCallBack, UBaseBuff*);
	FEndBuffCallBack OnEndBuffCallBack;
};
