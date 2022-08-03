// Copyright Epic Games, Inc. All Rights Reserved.

#include "KRootmotionExportFunctionLib.h"
#include "MathUtil.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "EditorDirectories.h"
#include "Widgets/SWindow.h"
#include "Misc/FileHelper.h"

#define LOCTEXT_NAMESPACE "KRootmotionExportFunctionLib"

void UKRootmotionExportFunctionLib::GetAnimSequenceInfo(const UAnimSequence* AnimSequence, float FrameRate, FString& OutJsonString)
{
    auto SetField = [&](const FString& FieldName, const FString& FieldValue, bool IsStringValue, bool IsAppendComma)
    {
        OutJsonString.Append("\"");
        OutJsonString.Append(FieldName);
        OutJsonString.Append("\"");
        OutJsonString.Append(":");
        if (IsStringValue)
        {
            OutJsonString.Append("\"");
        }
        OutJsonString.Append(FieldValue);
        if (IsStringValue)
        {
            OutJsonString.Append("\"");
        }
        if (IsAppendComma)
        {
            OutJsonString.Append(",");
        }
    };

    OutJsonString.Append("{");
    SetField("path", AnimSequence->GetPathName(), true, true);
    SetField("animName", AnimSequence->GetName(), true, true);

    OutJsonString.Append("\"data\":");
    OutJsonString.Append("[");

    int32 Count = (int32)FMathd::Ceil(AnimSequence->GetPlayLength() / FrameRate);
    for (int32 i = 0; i < Count; i++)
    {
        OutJsonString.Append("{");

        FTransform Transform = AnimSequence->ExtractRootMotion(i * FrameRate, (i + 1) * FrameRate, true);
        SetField("time", FString::SanitizeFloat((i + 1) * FrameRate), false, true);
        SetField("x", FString::SanitizeFloat(Transform.GetLocation().X), false, true);
        SetField("y", FString::SanitizeFloat(Transform.GetLocation().Y), false, true);
        SetField("z", FString::SanitizeFloat(Transform.GetLocation().Z), false, true);
        SetField("yaw", FString::SanitizeFloat(Transform.GetRotation().Z), false, false);


        OutJsonString.Append("}");
        if (i + 1 < Count)
        {
            OutJsonString.Append(",");
        }
    }
    OutJsonString.Append("]");
    OutJsonString.Append("}");

}

void UKRootmotionExportFunctionLib::ExportTransformData(const TArray<FAssetData> SelectedAssets, float FrameRate)
{
    int32 MaxCount = 0;
    for (int32 i = 0; i < SelectedAssets.Num(); i++)
    {
        if (UAnimSequence* AnimSequence = Cast<UAnimSequence>(SelectedAssets[i].GetAsset()))
        {
            MaxCount++;
        }
    }
    if (MaxCount <= 0)
    {
        return;
    }

    FString JsonString;
    JsonString.Append("[");

    int CurCount = 0;
    for (int32 i = 0; i < SelectedAssets.Num(); i++)
    {
        if (UAnimSequence* AnimSequence = Cast<UAnimSequence>(SelectedAssets[i].GetAsset()))
        {
            UKRootmotionExportFunctionLib::GetAnimSequenceInfo(AnimSequence, FrameRate, JsonString);
            if (++CurCount < MaxCount)
            {
                JsonString.Append(",");
            }
        }
    }
    JsonString.Append("]");
    
    UKRootmotionExportFunctionLib::SaveFile(JsonString);
}

void UKRootmotionExportFunctionLib::SaveFile(const FString& FileContent)
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

    if (DesktopPlatform)
    {
        //Get parent window for dialogs
        TSharedPtr<SWindow> RootWindow = FGlobalTabmanager::Get()->GetRootWindow();

        void* ParentWindowWindowHandle = NULL;

        if (RootWindow.IsValid() && RootWindow->GetNativeWindow().IsValid())
        {
            ParentWindowWindowHandle = RootWindow->GetNativeWindow()->GetOSWindowHandle();
        }


        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

        const FString Title = LOCTEXT("ExportJsonToFolderTitle", "Choose a destination folder for the Json file(s)").ToString();


        // One file only, ask for full filename.
        // Can set bFolderValid from the SaveFileDialog call as the window will handle 
        // duplicate files for us.
        TArray<FString> TempDestinationNames;
        bool bSave = DesktopPlatform->SaveFileDialog(
            ParentWindowWindowHandle,
            Title,
            FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_EXPORT),
            "",
            "JSON  |*.json",
            EFileDialogFlags::None,
            TempDestinationNames
        );

        if (!bSave)
        {
            // Canceled
            return;
        }
        check(TempDestinationNames.Num() == 1);

        FFileHelper::SaveStringToFile(FileContent, *TempDestinationNames[0]);

    }

}
#undef LOCTEXT_NAMESPACE