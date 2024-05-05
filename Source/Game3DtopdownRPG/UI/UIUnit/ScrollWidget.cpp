// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollWidget.h"
#include "Components/GridSlot.h"

UScrollWidget::UScrollWidget(): TotalCol(0), TotalRow(0), CurCol(0), CurRow(0)
{
}

void UScrollWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	GridContents = GetOwnUI<UGridPanel>(TEXT("GridPanel_Contents"));
}

void UScrollWidget::AddWidgets(TArray<UBaseWidget*> widgets)
{
    if (widgets.Num() <= 0) return;
    if (nullptr == GridContents)
    {
        return;
    }

    for (int i = 0; i < widgets.Num(); ++i)
    {
        if (nullptr == widgets[i]) continue;
        UGridSlot* GridSlot = GridContents->AddChildToGrid(widgets[i]);
        if (nullptr != GridSlot)
        {
            GridSlot->SetColumn(CurCol);
            GridSlot->SetRow(CurRow);
        }

        ++CurCol;
        if (CurCol >= TotalCol) 
        {
            CurCol = 0;
            CurRow += 1;
        }
    }
}

void UScrollWidget::AddWidget(UBaseWidget* widget)
{
    if (nullptr == GridContents || nullptr == widget)
    {
        return;
    }

    UGridSlot* GridSlot = GridContents->AddChildToGrid(widget);
    if (nullptr != GridSlot)
    {
        GridSlot->SetColumn(CurCol);
        GridSlot->SetRow(CurRow);
    }

    ++CurCol;
    if (CurCol >= TotalCol)
    {
        CurCol = 0;
        CurRow += 1;
    }
}

void UScrollWidget::ClearAll()
{
    if (nullptr == GridContents)
        GridContents->ClearChildren();
}
