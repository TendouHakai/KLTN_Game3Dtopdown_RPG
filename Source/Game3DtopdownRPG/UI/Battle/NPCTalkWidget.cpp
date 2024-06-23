// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCTalkWidget.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"

void UNPCTalkWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	NameNPCText = GetOwnUI<UTextBlock>(TEXT("TextBlock_Name"));
	NpcTalkText = GetOwnUI<URichTextBlock>(TEXT("RichTextBlock_Talk"));

	AnimTalkStart = GetWidgetAnimation(TEXT("TalkStart"));
	AnimTalkNext = GetWidgetAnimation(TEXT("TalkNext"));
	AnimNext = GetWidgetAnimation(TEXT("NextAnim"));
}

void UNPCTalkWidget::SetInfo(FText nameNPC, TArray<FText> talks)
{
	this->NameNPC = NameNPC;
	this->Talks.Empty();
	this->Talks = talks;

	NameNPCText->SetText(NameNPC);
	talkIndex = 0;
	StartTalk();
}

void UNPCTalkWidget::StartTalk()
{
	PlayAnimation(AnimTalkStart);
	if (NpcTalkText == nullptr || Talks.Num() == 0)
	{
		EndTalk();
		return;
	}
		
	NpcTalkText->SetText(Talks[talkIndex++]);
}

void UNPCTalkWidget::NextTalk()
{
	if (NpcTalkText == nullptr || talkIndex >= Talks.Num())
	{
		EndTalk();
		return;
	}

	PlayAnimation(AnimTalkNext);
	NpcTalkText->SetText(Talks[talkIndex++]);
}

void UNPCTalkWidget::EndTalk_Implementation()
{
	OnEndTalk_Delegate.Broadcast();
	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}
