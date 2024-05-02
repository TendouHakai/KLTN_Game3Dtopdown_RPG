// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroBuffMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "TableMgr.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"

FBuffInfoRecord* UHeroBuffMgr::GetHeroBuffInfoRecord(int32 BuffType, int32 BuffCondition)
{
	UDataTable* table = GetMgr(UTableMgr)->BuffInfoTable;
	if (nullptr != table)
	{
		TArray<FName> rownames = table->GetRowNames();
		for (const FName& rowname : rownames)
		{
			FBuffInfoRecord* buffinforecord = table->FindRow<FBuffInfoRecord>(rowname, FString(""));
			if (nullptr != buffinforecord)
			{
				if (buffinforecord->BuffType == BuffType && buffinforecord->BuffCondition == BuffCondition)
					return buffinforecord;
			}
		}
	}

	return nullptr;
}
