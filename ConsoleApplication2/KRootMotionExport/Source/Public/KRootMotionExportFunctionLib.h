// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "KRootmotionExportFunctionLib.generated.h"

UCLASS()
class UKRootmotionExportFunctionLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Rootmotion")
    static void ExportTransformData(const TArray<FAssetData> SelectedAssets, float FrameRate);
private:
    static void GetAnimSequenceInfo(const UAnimSequence* AnimSequence, float FrameRate, FString& OutJsonString);
    static void SaveFile(const FString& FileContent);

};