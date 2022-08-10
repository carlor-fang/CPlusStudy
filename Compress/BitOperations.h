#include <iostream>
#include <fstream>
#include <streambuf>
#include "assert.h"

using namespace std;

typedef unsigned char Byte;


class BitOperations 
{
public:
    static void WriteOneBit(Byte* Buffer, int Value, int& BitPos)
    {
        int Index = BitPos / 8;
        int Last = BitPos % 8;
        Byte SrcValue = Buffer[Index];
        switch (Value)
        {
        case 1:
            SrcValue |= (1 << Last);
            break;
        case 0:
            SrcValue &= (~(1 << Last));
            break;
        default:
            return;
        }
        Buffer[Index] = SrcValue;
        BitPos++;
    }

    static void ReadOneBit(Byte* Buffer, int BitPos, int& RetBit)
    {
        int Index = BitPos / 8;
        int Last = BitPos % 8;
        Byte SrcValue = Buffer[Index];

        RetBit = (SrcValue >> Last) & 0x1;
    }

    template<typename T>
    static void WriteDataToBuffer(Byte* Buffer, T Value, int& BitPos)
    {
        int ValueSize = sizeof(Value);

        for (int i = 0; i < ValueSize; i++)
        {
            Byte ByteData = ((Byte*)&Value)[i];
            for (int j = 0; j < 8; j++)
            {
                int BitData;
                ReadOneBit(&ByteData, j, BitData);
                WriteOneBit(Buffer, BitData, BitPos);
            }
        }
    }

    template<typename T>
    static void ReadDataFromBuffer(Byte* Buffer, T& Value, int BitPos)
    {
        int ValueSize = sizeof(Value);

        Byte DescByteData = 0;
        for (int i = 0; i < ValueSize; i++)
        {
            DescByteData = 0;
            for (int j = 0; j < 8; j++)
            {
                int BitData;
                ReadOneBit(Buffer, BitPos + j + i * 8, BitData);
                int Pos = j;
                WriteOneBit(&DescByteData, BitData, Pos);
            }
            ((Byte*)&Value)[i] = DescByteData;
        }
    }
};