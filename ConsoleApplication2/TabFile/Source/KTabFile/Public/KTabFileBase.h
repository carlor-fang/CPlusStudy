// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


template<typename TabFileClass>
class FKTabFileSingleton
{
public:
    static TabFileClass& Get()
    {
        static TabFileClass Instance;
        return Instance;
    }
};

template<typename TabFileClass, typename TabDataKeyType, typename TabData>
class FKTabFileBase : public FKTabFileSingleton<TabFileClass>
{
public:
    virtual ~FKTabFileBase() {}

    virtual bool Load(const FString& Name)
    {
        if (IsLoaded)
        {
            return IsLoaded;
        }
        FString FileName = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("KTabFile"), TEXT("Content"), Name);

        IsLoaded = true;
        TArray<FString> Columns;

        FFileHelper::LoadFileToStringWithLineVisitor(*FileName, [&](FStringView Line) {
            const TCHAR* LineData = Line.GetData();
            if (LineData != '\0' )
            {
                FString LineString(LineData);
                if (Columns.Num() == 0)
                {
                    LineString.ParseIntoArray(Columns, TEXT("\t"));
                }
                else
                {
                    TArray<FString> ColumnDatas;
                    LineString.ParseIntoArray(ColumnDatas, TEXT("\t"));
                    if (ColumnDatas.Num() == Columns.Num())
                    {
                        TabData Data;
                        Data.RegisterParams();
                        Data.Load(Columns, ColumnDatas);
                        Datas.Add(Data.GetKey(), Data);
                    }
                }
            }
        });
        return IsLoaded;
    }
protected:
    bool IsLoaded;
    TMap<TabDataKeyType, TabData> Datas;
};
