
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/Image.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "EquipmentSlotWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEquipmentSlotDrop_DelegateEx, int32, Output, UEquipmentSlotWidget*, Output02);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FEquipmentSlotTap_DelegateEx, int32, Output, UEquipmentSlotWidget*, Output02);

struct FGameItemInfo;
class UInventoryEquipContainerWidget;
class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UEquipmentSlotWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetHeroCharacter(ABaseCharacter* hero);

	UFUNCTION(BlueprintCallable)
	void EquipItemToSlot(FGameItemEquipmentInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	void EmptyUI();

	UFUNCTION(BlueprintCallable)
	void OnDropEvent(FGameItemEquipmentInfo info);

	template<class T>
	void SetDropEventEx(T* owner)
	{
		OwnerDropDelegateEx.Unbind();
		OwnerDropDelegateEx.BindDynamic(owner, &T::OnDropEquipSlot);
	}

	UFUNCTION(BlueprintCallable)
	void OnTapEvent();

	template<class T>
	void SetTapEventEx(T* owner)
	{
		OwnerTapDelegateEx.Unbind();
		OwnerTapDelegateEx.BindDynamic(owner, &T::OnTapEquipSlot);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UInventoryEquipContainerWidget* GetInventoryEquipment() { return inventoryEquipment; }

	virtual void Update() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EItemEquipPosition EquipmentPosition;
protected:
	void setImageIcon();
	
protected:
	UImage* imageIcon;
	UImage* imageLock;
	UInventoryEquipContainerWidget* inventoryEquipment;

	ABaseCharacter* character;

	FEquipmentSlotDrop_DelegateEx OwnerDropDelegateEx;
	FEquipmentSlotTap_DelegateEx OwnerTapDelegateEx;
};
