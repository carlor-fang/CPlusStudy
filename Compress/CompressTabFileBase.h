// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "CompressTabFileBase.h"

using namespace std;
#define Define_Size 1024

template<typename TabFileClass, typename TabDataKeyType, typename TabData>
class CompressTabFileBase
{
public:
    CompressTabFileBase() 
    {
    }

    virtual ~CompressTabFileBase()
    {
        if (Buffer)
        {
            free(Buffer);
            Buffer = nullptr;
        }
    }
    
    void ResetBufferSize(int Size)
    {
        if (!Buffer)
        {
            Buffer = (char*)malloc(Size);
            BufferSize = Size;
            memset(Buffer, 0, BufferSize);
        }
        else
        {
            char* p = (char*)realloc(Buffer, Size);
            assert(p);
            Buffer = p;
            BufferSize = Size;
        }
    }

    template<typename T>
    int GetKey(T Key)
    {
    }

    template<>
    int GetKey(int Key)
    {
        return Key;
    }

    template<>
    int GetKey(const string& Key)
    {
        return GetHash(Key);
    }

    int GetHash(const string& Key) 
    {
        int Hash = 0;
        for (int i = 0; i < Key.length(); i++)
        {
            Hash = Key[i] + 65599 * Hash;
        }
        return (Hash & 0x7FFFFFFF);
    }

    int ParseInToArray(const string& SrcString, vector<string>& OutArray, const char* Delim)
    {
        OutArray.clear();
        int Len = strlen(Delim);

        if (SrcString.length() && Delim)
        {
            int Index = 0;
            int Pos = SrcString.find(Delim, Index);
            while (Pos >= 0)
            {
                OutArray.push_back(SrcString.substr(Index, Pos - Index));
                Index = Pos + Len;
                Pos = SrcString.find(Delim, Index);
            }
            OutArray.push_back(SrcString.substr(Index, SrcString.length() - Index));
        }

        return OutArray.size();
    }

    virtual bool Load(const string& Name)
    {
        ifstream TabFile(Name);
        if (!TabFile)
        {
            return false;
        }


        string Line;
        getline(TabFile, Line);
        vector<string> Columns;
        ParseInToArray(Line, Columns, "\t");

        int Size = 0;
        vector<TabData*> Datas;
        vector<string> LineData;
        while (getline(TabFile, Line))
        {
            ParseInToArray(Line, LineData, "\t");
            TabData* Data = new TabData();
            Data->RegisterParams();
            Size += Data->Load(Columns, LineData);
            Datas.push_back(Data);
        }
        if (Datas.size() == 0)
        {
            TabFile.close();
            return false;
        }

        ResetBufferSize(Size + sizeof(int));

        int HeadBitPos = 0;
        int Count = Datas.size();
        BitOperations::WriteDataToBuffer((Byte*)Buffer, Count, HeadBitPos);
        // (4 (key ) + 4 (offset)) * Datas.size() * 8(one byte 8 bit)
        int BitBodyPos = (sizeof(int) + (sizeof(int) * 2) * Datas.size()) * 8;
        for (int i = 0; i < Datas.size(); i++)
        {
            // write head
            // write key
            BitOperations::WriteDataToBuffer((Byte*)Buffer, GetKey(Datas[i]->GetKey()), HeadBitPos);
            // write bit offset
            BitOperations::WriteDataToBuffer((Byte*)Buffer, BitBodyPos, HeadBitPos);

            // write body
            Datas[i]->WriteToBuffer(Buffer, BitBodyPos);
        }

        for (int i = Datas.size() - 1; i >= 0; i--)
        {
            delete Datas[i];
        }
        Datas.clear();
        ResetBufferSize(ceil(BitBodyPos / 8));
        TabFile.close();
        return true;
    }

    virtual bool Find(TabDataKeyType Key, TabData& Data)
    {
        int Count = 0;
        int IntSize = sizeof(int);
        memcpy(&Count, Buffer, IntSize);
        
        int DataBitOffset = -1;
        int Pos = IntSize;
        int IntKey = GetKey(Key);
        for (int i = 0; i < Count; i++)
        {
            int DataKey = 0;
            memcpy(&DataKey, Buffer + Pos, IntSize);
            Pos += IntSize;
            if (DataKey != IntKey)
            {
                Pos += IntSize;
                continue;
            }
            memcpy(&DataBitOffset, Buffer + Pos, IntSize);
            break;
        }

        if (DataBitOffset < 0)
        {
            return false;
        }

        Data.LoadFromBuffer(Buffer, DataBitOffset);
        return true;
    }

protected:
    char* Buffer;
    int BufferSize;
};
