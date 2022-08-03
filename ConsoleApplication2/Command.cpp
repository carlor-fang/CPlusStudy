#include <iostream>
#include "Command.h"
#include "assert.h"

Command::Command()
{
    std::cout << "default constructor" << std::endl;
}

Command::Command(const Command& InCommand)
{
    std::cout << "copy constructor" << std::endl;
}

Command::~Command()
{
    std::cout << "destructor" << std::endl;
}

class NumberParseException {};
bool IsNumber(char* Arg) {
    if (!Arg)
    {
        return false;
    }
    int Len = strlen(Arg);
    if (Len == 0)
    {
        return false;
    }

    bool IsDouble = false;
    bool Ret = true;
    for (int i = 0; i < Len; i++) {
        if (i == 0 && (Arg[i] == '-' || Arg[i] == '+'))
        {
            continue;
        }
        if (i > 0 && i != Len - 1 && Arg[i] == '.' && !IsDouble)
        {
            IsDouble = true;
            continue;
        }
        if (!isdigit(Arg[i])) {
            Ret = false;
            break;
        }
    }
    return Ret;
}
template<typename T>
T ParseNumber(char* Arg, EValueType ValueType) throw(NumberParseException) {
    if (!IsNumber(Arg))
        throw NumberParseException();
    if (ValueType == EValueType::Int)
    {
        return atoi(Arg);
    }
    else if (ValueType == EValueType::Double)
    {
        return atof(Arg);
    }
}

bool ParseBool(char* Arg)
{
    if (_stricmp(Arg, "true") == 0)
    {
        return true;
    }
    else if (_stricmp(Arg, "false"))
    {
        return false;
    }
    else if (strcmp(Arg, "0") == 0)
    {
        return false;
    }

    return true;
}

bool Command::Parse(int ArgCount, char** Args)
{
    // Args[0] 是app名
    // 参数从 1 开始
    // 1: CommandName; ... Args
    int RealArgStart = 2;
    if (ArgCount < RealArgStart)
    {
        std::cout << "blank command" << std::endl;
        return false;
    }
    CommandMap::iterator Iter = Commands.find(Args[1]);
    if (Iter == Commands.end())
    {
        return false;
    }
    int RealArgCount = ArgCount - RealArgStart;

    std::vector<void*> VectorArg;
    CommandInfo* Info = Iter->second;
    for (int i = 0; i < Info->ArgTypes.size(); i++)
    {
        if (i + 1 <= RealArgCount)
        {
            // 
            char* StrArg = Args[i + RealArgStart];
            switch (Info->ArgTypes[i])
            {
            case EValueType::Int:
                try 
                {
                    int IntValue = ParseNumber<int>(StrArg, EValueType::Int);
                    VectorArg.push_back(&IntValue);
                }
                catch (NumberParseException) 
                {
                    std::cout << "int arg type is invalid" << std::endl;
                    return false;
                }
                break;
            case EValueType::Double:
                try
                {
                    double DoubleValue = ParseNumber<double>(StrArg, EValueType::Double);
                    VectorArg.push_back(&DoubleValue);
                }
                catch (NumberParseException)
                {
                    std::cout << "double arg type is invalid" << std::endl;
                    return false;
                }
                break;
            case EValueType::Bool:
                {
                    bool BoolValue = ParseBool(StrArg);
                    VectorArg.push_back(&BoolValue);
                }
                break;
            default:
                VectorArg.push_back(StrArg);
                break;
            }
        }
        else
        {
            // 没有传的参数用默认值填充
            switch (Info->ArgTypes[i])
            {
            case EValueType::Int:
                {
                    int IntValue = 0;
                    VectorArg.push_back(&IntValue);
                }
                break;
            case EValueType::Double:
                {
                    double DoubleValue = 0.f;
                    VectorArg.push_back(&DoubleValue);
                }
                break;
            case EValueType::Bool:
                {
                    bool BoolValue = true;
                    VectorArg.push_back(&BoolValue);
                }
                break;
            default:
                {
                    const char* StringValue = "";
                    VectorArg.push_back(&StringValue);
                }
                break;
            }
        }
    }
    Info->Callback(Info, VectorArg);
    return true;
}

int Split(const char* Args, int StartIndex, std::string& OutArg)
{
    int Len = strlen(Args);
    int Index = StartIndex;
    OutArg = "";
    while (Index < Len)
    {
        if (Args[Index] == DELIMITER)
        {
            return Index + 1;
        }
        else
        {
            OutArg += Args[Index];
        }
        Index++;
    }

    return Index;
}

bool Command::Register(const char* CommandName, const char* CommandArg, CallbackFunc Callback)
{
    if (!Callback)
    {
        return false;
    }
    CommandMap::iterator Iter = Commands.find(CommandName);
    if (Iter != Commands.end())
    {
        return false;
    }
    size_t Len = strlen(CommandName);
    char* Name = (char*)malloc(Len + 1);
    assert(Name);
    memcpy(Name, CommandName, Len);
    Name[Len] = 0;

    CommandInfo* Info = new CommandInfo(Callback);

    int StartIndex = 0;
    Len = strlen(CommandArg);
    std::string ValueType;
    StartIndex = Split(CommandArg, StartIndex, ValueType);
    while (ValueType.length() > 0)
    {
        if (_stricmp(ValueType.c_str(), "Int") == 0)
        {
            Info->ArgTypes.push_back(EValueType::Int);
        }
        else if (_stricmp(ValueType.c_str(), "Double") == 0)
        {
            Info->ArgTypes.push_back(EValueType::Double);
        }
        else if (_stricmp(ValueType.c_str(), "String") == 0)
        {
            Info->ArgTypes.push_back(EValueType::String);
        }
        else if (_stricmp(ValueType.c_str(), "Bool") == 0)
        {
            Info->ArgTypes.push_back(EValueType::Bool);
        }
        else 
        {
            std::cout << "unsupported arg type" << std::endl;
            delete Info;
            return false;
        }
        StartIndex = Split(CommandArg, StartIndex, ValueType);
    }

    Commands[Name] = Info;
    return true;
}