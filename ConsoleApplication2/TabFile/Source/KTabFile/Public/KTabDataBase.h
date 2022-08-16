// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

enum EFieldType
{
    EF_INT = 0,
    EF_STRING
};

struct FKTabDataField
{
public:
    FString Key;
    int32 Offset;
    EFieldType FieldType;
};

template<typename TabData>
class FKTabDataBase
{
public:
    FKTabDataBase() {}
    virtual ~FKTabDataBase() {}

    virtual void RegisterParams() {};

    void RegisterField(const FString& Key, int32 Offset, int32 Field)
    {
        FKTabDataField& FieldData = FieldMap.FindOrAdd(Key);
        FieldData.Key = Key;
        FieldData.Offset = Offset;
        FieldData.FieldType = EFieldType::EF_INT;
    }

    void RegisterField(const FString& Key, int32 Offset, const FString& Field)
    {
        FKTabDataField& FieldData = FieldMap.FindOrAdd(Key);
        FieldData.Key = Key;
        FieldData.Offset = Offset;
        FieldData.FieldType = EFieldType::EF_STRING;
    }

    void Load(const TArray<FString> ColumnNames, const TArray<FString> ColumnDatas)
    {
        for (int32 i = 0; i < ColumnNames.Num(); i++)
        {
            FKTabDataField* Field = FieldMap.Find(ColumnNames[i]);
            if (!Field)
            {
                Field = FieldMap.Find("descriptors");
            }
            if (Field)
            {
                switch (Field->FieldType)
                {
                    case EFieldType::EF_STRING:
                        FTabFileFieldWrite<FString>::Write(this, Field->Offset, ColumnDatas[i]);
                        //*(FString*)((char*)this + Field->Offset) = ColumnDatas[i];
                        break;
                    default:
                        FTabFileFieldWrite<int32>::Write(this, Field->Offset, FCString::Atoi(*ColumnDatas[i]));
                        //*(int32*)((char*)this + Field->Offset) = FCString::Atoi(*ColumnDatas[i]);
                        break;
                }
            }
        }
    }
protected:
    TMap<FString, FKTabDataField> FieldMap;

    typedef TabData TabDataClass;
};

template<typename T>
class FTabFileFieldWrite
{
public:
    static bool Write(void* File, int32 Offset, const T& Value)
    {
        return false;
    }
};

template<>
class FTabFileFieldWrite<int32>
{
public:
    static bool Write(void* File, int32 Offset, int32 Value)
    {
        *(int32*)((char*)File + Offset) = Value;
        return true;
    }
};

template<>
class FTabFileFieldWrite<FString>
{
public:
    static bool Write(void* File, int32 Offset, const FString& Value)
    {
        *(FString*)((char*)File + Offset) = Value;
        return true;
    }
};