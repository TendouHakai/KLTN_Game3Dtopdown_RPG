// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollWidget.h"
#include "Components/GridSlot.h"
#include "InventoryContainerWidget.h"
#include "InventoryEquipContainerWidget.h"

UScrollWidget::UScrollWidget()
{
}

void UScrollWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

    GridContents = GetOwnUI<UGridPanel>(TEXT("GridPanel_Contents"));
    // create visible all child in grid content
    if (nullptr == GridContents) return;
    if (nullptr == ChildBP) return;
    if (GridContents->GetChildrenCount() > 0) return;

    for (int indexchild = 0; indexchild < VisibleRowCnt * ChildCntPerRow; ++indexchild)
    {
        UUserWidget* ChildWidget = CreateWidget<UUserWidget>(GetWorld(), ChildBP);
        UUIUnitWidget* unitWidget = Cast<UUIUnitWidget>(ChildWidget);
        if (nullptr != unitWidget) unitWidget->InitUnit(GameMode);

        UGridSlot* GridSlot = GridContents->AddChildToGrid(ChildWidget);

        int32 ColumnIdx = indexchild % ChildCntPerRow;
        int32 RowIdx = indexchild / ChildCntPerRow;

        //if (Orientation == EOrientation::Orient_Horizontal)
        //    Swap(ColumnIdx, RowIdx);

        GridSlot->SetColumn(ColumnIdx);
        GridSlot->SetRow(RowIdx);
    }
}

void UScrollWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UScrollWidget::ClearAll()
{
    if (nullptr == GridContents)
        GridContents->ClearChildren();
}

void UScrollWidget::SetChildCount(int32 InChildCount)
{
    this->childcount = InChildCount;
    Update();
}

void UScrollWidget::Update()
{
    Super::Update();

    // update children
    for (int indexchild = 0; indexchild < GridContents->GetChildrenCount(); ++indexchild)
    {
        UWidget* ChildWidget = GridContents->GetChildAt(indexchild);
        //int32 ChildDataIdx = HeadIdx + indexchild;

        if (childcount <= indexchild)
        {
            if (Cast<UInventoryContainerWidget>(ChildWidget) != nullptr)
                Cast<UInventoryContainerWidget>(ChildWidget)->EmptyUI();
            else if (Cast<UInventoryEquipContainerWidget>(ChildWidget) != nullptr)
                Cast<UInventoryEquipContainerWidget>(ChildWidget)->EmptyUI();
            continue;
        }

        ChildWidget->SetVisibility(ESlateVisibility::Visible);
        ChildUpdateEvent.ExecuteIfBound(ChildWidget, indexchild);
    }
}
