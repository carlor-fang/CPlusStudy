// Copyright Epic Games, Inc. All Rights Reserved.

#include "KRootMotionExportCommandlet.h"
#include "Misc/Parse.h"
#include "Engine/ObjectLibrary.h"
#include "KRootmotionExportFunctionLib.h"

DEFINE_LOG_CATEGORY_STATIC(KRootMotionExportCommandlet, Log, All);

UKRootMotionExportCommandlet::UKRootMotionExportCommandlet()
{
    LogToConsole = true;
}

int32 UKRootMotionExportCommandlet::Main(const FString& Params)
{
    UE_LOG(KRootMotionExportCommandlet, Display, TEXT("Export Start!"));
    TArray<FString> Tokens;
    TArray<FString> Switches;
    TMap<FString, FString> ParamVals;
    ParseCommandLine(*Params, Tokens, Switches, ParamVals);

    FString AssetPath = ParamVals.FindRef(TEXT("path"));
    UE_LOG(KRootMotionExportCommandlet, Display, TEXT("Path = %s"), *AssetPath);
    FParse::Value(*Params, TEXT("path="), AssetPath);
    UE_LOG(KRootMotionExportCommandlet, Display, TEXT("Path = %s"), *AssetPath);
    FString StrFrameRate = ParamVals.FindRef(TEXT("fr"));
    float FrameRate = FCString::Atof(*StrFrameRate);
    UE_LOG(KRootMotionExportCommandlet, Display, TEXT("FrameRate = %f"), FrameRate);
    FParse::Value(*Params, TEXT("fr="), FrameRate);
    UE_LOG(KRootMotionExportCommandlet, Display, TEXT("FrameRate = %f"), FrameRate);

    UObjectLibrary* ObjLib = UObjectLibrary::CreateLibrary(UObject::StaticClass(), false, GIsEditor);
    ObjLib->AddToRoot();
    ObjLib->LoadAssetDataFromPath(AssetPath);
    ObjLib->LoadAssetsFromAssetData();

    TArray<FAssetData> AssetDatas;
    ObjLib->GetAssetDataList(AssetDatas);

    UKRootmotionExportFunctionLib::ExportTransformData(AssetDatas, FrameRate);

    return 0;
}