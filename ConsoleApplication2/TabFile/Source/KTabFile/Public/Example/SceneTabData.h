// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KTabFileMacro.h"
#include "KTabFileBase.h"

TAB_FILE_DATA(FSceneTabData)
{
public:
    int SceneId;
    FString Descriptors;
    // FCustomType CustomValue; // 高级要求，可以支持自定义类型解析

    FSceneTabData()
        : SceneId(-1)
    {}
//
    TAB_FILE_DATA_SINGLE_KEY(int, SceneId);
//
    virtual void RegisterParams() override
    {
        TAB_FILE_DATA_REGISTER(SceneId, "id");
        TAB_FILE_DATA_REGISTER(Descriptors, "descriptors");
        // TAB_FILE_DATA_REGISTER(CustomValue, "custom");
    }

    int GetSceneId()
    {
        return SceneId;
    }
};

TAB_FILE_WITH_PATH(FSceneTabFile, FSceneTabData, "common/scene/scene.tab")
