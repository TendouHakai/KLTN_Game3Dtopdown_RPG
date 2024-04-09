// Fill out your copyright notice in the Description page of Project Settings.


#include "HitFlash.h"

UHitFlash::UHitFlash()
{
	//PrimaryComponentTick.bCanEverTick = true;
}


void UHitFlash::Flash(const FLinearColor& EmissiveColor, float FlashTime)
{
	for (int32 MatIdx = 0; MatIdx < DynamicMats.Num(); ++MatIdx)
	{
		UMaterialInstanceDynamic* Mat = DynamicMats[MatIdx];
		Mat->SetVectorParameterValue(HitFlashColorPramName, EmissiveColor);
	}

	GetWorld()->GetTimerManager().SetTimer(BackTimer, this, &UHitFlash::BackToOriginColor, FlashTime, false);
}

// Called when the game starts
void UHitFlash::BeginPlay()
{
	Super::BeginPlay();

	UMeshComponent* TargetMesh = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(UMeshComponent::StaticClass()));
	if (!TargetMesh) return;

	TArray<UMaterialInterface*> OriginMats = TargetMesh->GetMaterials();

	DynamicMats.Empty(OriginMats.Num());
	OriginEmissiveColors.Empty(OriginMats.Num());

	// 다이나믹 머테리얼 만들고 원래 이미시브 색 저장해둠
	for (int32 MatIdx = 0; MatIdx < OriginMats.Num(); ++MatIdx)
	{
		UMaterialInterface* OriginMat = OriginMats[MatIdx];
		if (!OriginMat) continue;

		if (!OriginMat->IsA(UMaterialInstanceDynamic::StaticClass()))
		{
			UMaterialInstanceDynamic* DynamicMat = UMaterialInstanceDynamic::Create(OriginMat, this);
			TargetMesh->SetMaterial(MatIdx, DynamicMat);
			DynamicMats.Add(DynamicMat);
		}
		else
		{
			DynamicMats.Add((UMaterialInstanceDynamic*)OriginMat);
		}

		FLinearColor OriginColor = FLinearColor::Black;
		OriginMat->GetVectorParameterDefaultValue(HitFlashColorPramName, OriginColor);

		OriginEmissiveColors.Add(OriginColor);
	}
}

void UHitFlash::BackToOriginColor()
{
	for (int32 MatIdx = 0; MatIdx < DynamicMats.Num(); ++MatIdx)
	{
		UMaterialInstanceDynamic* Mat = DynamicMats[MatIdx];
		FLinearColor OriginColor = OriginEmissiveColors[MatIdx];

		Mat->SetVectorParameterValue(HitFlashColorPramName, OriginColor);
	}
}


