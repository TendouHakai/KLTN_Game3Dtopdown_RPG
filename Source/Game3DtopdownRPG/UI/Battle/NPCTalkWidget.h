// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "NPCTalkWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTalk);

UCLASS()
class GAME3DTOPDOWNRPG_API UNPCTalkWidget : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetInfo(FText nameNPC, TArray<FText> talks);

	UFUNCTION(BlueprintCallable)
	void StartTalk();
	UFUNCTION(BlueprintCallable)
	void NextTalk();

	UFUNCTION(BlueprintNativeEvent)
	void EndTalk();
	virtual void EndTalk_Implementation();

public:
	UPROPERTY(BlueprintAssignable, Category = "npc") FOnEndTalk OnEndTalk_Delegate;
protected:
	// UI
	UTextBlock* NameNPCText;
	URichTextBlock* NpcTalkText;

	FText NameNPC;
	TArray<FText> Talks;
	UWidgetAnimation* AnimTalkStart;
	UWidgetAnimation* AnimTalkNext;
	UWidgetAnimation* AnimNext;
	int talkIndex = 0;
};
