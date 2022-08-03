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
    FKTabDataField(const FString& InKey, int32 InOffset, EFieldType InFieldType) : Key(InKey), Offset(InOffset), FieldType(InFieldType) {};

    FString Key;
    int32 Offset;
    EFieldType FieldType;
};

//class FKTabIntField : public FKTabDataField
//{
//public:
//    FKTabIntField(const FString& InKey, int32 InOffset){};
//    virtual void SetData(const FString& InData) override 
//    {
//
//    };
//
//    int32 Data;
//};
//
//class FKTabStringField : public FKTabDataField
//{
//public:
//    FKTabStringField(const FString& InKey, int32 InOffset){};
//    virtual void SetData(const FString& InData) override {};
//
//    FString Data;
//};


template<typename TabData>
class FKTabDataBase
{
public:
    FKTabDataBase() {}
    virtual ~FKTabDataBase() {}

    virtual void RegisterParams() {};

    void RegisterField(const FString& Key, int32 Offset, int32 Field)
    {
        FKTabDataField Temp(Key, Offset, EFieldType::EF_INT);
        FieldMap.Add(Key, Temp);
    }

    void RegisterField(const FString& Key, int32 Offset, const FString& Field)
    {
        FKTabDataField Temp(Key, Offset, EFieldType::EF_STRING);
        FieldMap.Add(Key, Temp);
    }

    void Load(const TArray<FString> ColumnNames, const TArray<FString> ColumnDatas)
    {
        for (int32 i = 0; i < ColumnNames.Num(); i++)
        {
            FKTabDataField* Field = FieldMap.Find(ColumnNames[i]);
            if (Field)
            {
                switch (Field->FieldType)
                {
                    case EFieldType::EF_STRING:
                        *(FString*)((char*)this + Field->Offset) = ColumnDatas[i];
                        break;
                    default:
                        *(int32*)((char*)this + Field->Offset) = FCString::Atoi(*ColumnDatas[i]);
                        break;
                }
            }
        }
    }
protected:
    TMap<FString, FKTabDataField> FieldMap;

    typedef TabData TabDataClass;
};