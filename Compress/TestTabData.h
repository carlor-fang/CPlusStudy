// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CompressTabFileMacro.h"
#include "CompressTabFileBase.h"
#include <string>

TAB_FILE_DATA(TestTabData)
{
public:
    int Id;
    int SubId;
    std::string Desc;
    // FCustomType CustomValue; // 高级要求，可以支持自定义类型解析

    TestTabData()
        : Id(-1)
    {}
//
    TAB_FILE_DATA_SINGLE_KEY(int, Id);
//
    virtual void RegisterParams() override
    {
        TAB_FILE_DATA_REGISTER(Id, "id");
        TAB_FILE_DATA_REGISTER(SubId, "subid");
        TAB_FILE_DATA_REGISTER(Desc, "desc");
        // TAB_FILE_DATA_REGISTER(CustomValue, "custom");
    }
};

TAB_FILE_WITH_PATH(TestTabFile, TestTabData)
