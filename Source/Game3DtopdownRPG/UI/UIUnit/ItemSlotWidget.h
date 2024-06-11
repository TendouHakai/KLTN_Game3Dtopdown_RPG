// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "ItemSlotWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FItemSlotDrop_DelegateEx, int32, Output, UItemSlotWidget*, Output02);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FItemSlotTap_DelegateEx, int32, Output, UItemSlotWidget*, Output02);

class UInventoryContainerWidget;
class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UItemSlotWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void EquipItemToSlot(FGameItemInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	void EmptyUI();

	UFUNCTION(BlueprintCallable)
	void OnDropEvent(FGameItemInfo info);

	UFUNCTION(BlueprintCallable)
	void OnTapEvent();

	template<class T>
	void SetDropEventEx(T* owner)
	{
		OwnerDropDelegateEx.Unbind();
		OwnerDropDelegateEx.BindDynamic(owner, &T::OnDropItemSlot);
	}

	template<class T>
	void SetTapEventEx(T* owner)
	{
		OwnerTapDelegateEx.Unbind();
		OwnerTapDelegateEx.BindDynamic(owner, &T::OnTapItemSlot);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UInventoryContainerWidget* GetInventoryContainer() { return inventoryEquipment; }

	virtual void SetHeroCharacter(ABaseCharacter* hero);

	virtual void Update() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 EquipPosition;

protected:
	UInventoryContainerWidget* inventoryEquipment;

	FItemSlotDrop_DelegateEx OwnerDropDelegateEx;
	FItemSlotTap_DelegateEx OwnerTapDelegateEx;

	ABaseCharacter* character;
};
