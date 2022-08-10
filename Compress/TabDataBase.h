// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include <map>
#include "BitOperations.h"

using namespace std;

// 写死默认值。。。
#define DEFAULT_INT 1
#define DEFAULT_STRING "aa"

enum EFieldType
{
    EF_INT = 0,
    EF_STRING
};

struct TabDataField
{
public:
    string Key;
    int Offset;
    EFieldType FieldType;
};

template<typename T>
static T& TabFileGetFieldByOffset(void* Data, unsigned int Offset)
{
    return *(T*)((char*)Data + Offset);
}

template<typename TabData>
class TabDataBase
{
public:
    TabDataBase() { }
    virtual ~TabDataBase() 
    {
        FieldMap.clear();
        FieldKey.clear();
    }

    virtual void RegisterParams() {};

    void RegisterField(const string& Key, int Offset, int Field)
    {
        TabDataField FieldData;
        FieldData.Key = Key;
        FieldData.Offset = Offset;
        FieldData.FieldType = EFieldType::EF_INT;
        FieldMap.insert(make_pair(Key, FieldData));
        FieldKey.push_back(Key);
    }

    void RegisterField(const string& Key, int Offset, const string& Field)
    {
        TabDataField FieldData;
        FieldData.Key = Key;
        FieldData.Offset = Offset;
        FieldData.FieldType = EFieldType::EF_STRING;
        FieldMap.insert(make_pair(Key, FieldData));
        FieldKey.push_back(Key);
    }

    int Load(const vector<string>& ColumnNames, const vector<string>& ColumnDatas)
    {
        for (int i = 0; i < ColumnNames.size(); i++)
        {
            auto It = FieldMap.find(ColumnNames[i]);
            if (It != FieldMap.end())
            {
                string Data = ColumnDatas[i];
                TabDataField Field = It->second;
                switch (Field.FieldType)
                {
                    case EFieldType::EF_STRING:
                        {
                            string Temp = DEFAULT_STRING;
                            if (Data.length() > 0 && Data.compare(DEFAULT_STRING) != 0)
                            {
                                Temp = Data;
                            }
                            TabFileGetFieldByOffset<string>(this, Field.Offset) = Temp;
                            Size += Temp.size();
                        }
                        break;
                    default:
                        {
                            int Temp = DEFAULT_INT;
                            if (Data.length() > 0)
                            {
                                Temp = stoi(Data);
                            }
                            TabFileGetFieldByOffset<int>(this, Field.Offset) = Temp;
                            Size += sizeof(int);
                        }
                        break;
                }
            }
        }
        Size += ColumnNames.size() * sizeof(int);

        return Size;
    }

    void LoadFromBuffer(char* Buffer, int BitPos)
    {
        for (int i = 0; i < FieldKey.size(); i++)
        {
            string Key = FieldKey[i];
            auto It = FieldMap.find(FieldKey[i]);
            assert(It != FieldMap.end());

            auto Field = It->second;
            int BitValue;
            BitOperations::ReadOneBit((Byte*)(Buffer), BitPos, BitValue);
            
            BitPos++;
            switch (Field.FieldType)
            {
            case EFieldType::EF_STRING:
                {
                    string& Temp = TabFileGetFieldByOffset<string>(this, Field.Offset);
                    if (BitValue > 0)
                    {
                        Temp = "";
                        while (true)
                        {
                            char CharTemp = 0;
                            BitOperations::ReadDataFromBuffer((Byte*)(Buffer), CharTemp, BitPos);
                            BitPos += sizeof(char) * 8;
                            Temp.push_back(CharTemp);
                            if (CharTemp == 0)
                            {
                                break;
                            }
                        }
                    }
                    else 
                    {
                        Temp = DEFAULT_STRING;
                    }
                }
                break;
            default:
                {
                    int& Temp = TabFileGetFieldByOffset<int>(this, Field.Offset);
                    if (BitValue > 0)
                    {
                        int Value = 0;
                        BitOperations::ReadDataFromBuffer((Byte*)(Buffer), Value, BitPos);
                        BitPos += sizeof(int) * 8;
                        Temp = Value;
                    }
                    else
                    {
                        Temp = DEFAULT_INT;
                    }
                }
                break;
            }

        }
    }

    void WriteToBuffer(char* Buffer, int& BitBodyPos)
    {
        char* BodyBuffer = Buffer + BitBodyPos;

        for (int i = 0; i < FieldKey.size(); i++)
        {
            string Key = FieldKey[i];
            auto It = FieldMap.find(FieldKey[i]);
            assert(It != FieldMap.end());

            auto Field = It->second;

            switch (Field.FieldType)
            {
            case EFieldType::EF_STRING:
                {
                    string Temp = TabFileGetFieldByOffset<string>(this, Field.Offset);
                    if (Temp.compare(DEFAULT_STRING) != 0)
                    {
                        BitOperations::WriteOneBit((Byte*)Buffer, 1, BitBodyPos);
                        int Index = 0;
                        while (Index < Temp.length())
                        {
                            BitOperations::WriteDataToBuffer((Byte*)Buffer, Temp.at(Index), BitBodyPos);
                            Index++;
                        }
                        //结束符
                        BitOperations::WriteOneBit((Byte*)Buffer, 0, BitBodyPos);
                    }
                    else
                    {
                        BitOperations::WriteOneBit((Byte*)Buffer, 0, BitBodyPos);
                    }
                }
                break;
            default:
                {
                    int Temp = TabFileGetFieldByOffset<int>(this, Field.Offset);
                    if (Temp != DEFAULT_INT)
                    {
                        BitOperations::WriteOneBit((Byte*)Buffer, 1, BitBodyPos);
                        BitOperations::WriteDataToBuffer((Byte*)Buffer, Temp, BitBodyPos);
                    }
                    else
                    {
                        BitOperations::WriteOneBit((Byte*)Buffer, 0, BitBodyPos);
                    }
                }
                break;
            }
        }
    }

protected:
    map<string, TabDataField> FieldMap;
    vector<string> FieldKey;
    // 预估最大值
    int Size;
    typedef TabData TabDataClass;
};