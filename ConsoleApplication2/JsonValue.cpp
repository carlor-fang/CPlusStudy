#include "JsonValue.h"
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <sstream>

JsonValue::JsonValue()
    : JsonType(EJsonType::Null)
{
    std::cout << "default constructor" << std::endl;
}

JsonValue::~JsonValue()
{
    switch (JsonType)
    {
        case EJsonType::Object:
        {
            for (JsonObject::iterator Iter = ObjectValue->begin(); Iter != ObjectValue->end(); Iter++)
            {
                delete Iter->second;
            }
            delete ObjectValue;
            break;
        }
        case EJsonType::Array:
        {
            for (JsonArray::iterator Iter = ArrayValue->begin(); Iter != ArrayValue->end(); Iter++)
            {
                delete *Iter;
            }
            delete ArrayValue;
            break;
        }
        case EJsonType::String:
        {
            delete StringValue;
        }
    }
}

JsonValue::JsonValue(const std::wstring& Value)
{
    std::cout << "wstring constructor" << std::endl;
    JsonType = EJsonType::String;
    StringValue = new std::wstring(Value);
}

JsonValue::JsonValue(const wchar_t* Value)
{
    std::cout << "wchar constructor" << std::endl;
    JsonType = EJsonType::String;
    StringValue = new std::wstring(Value);
}

JsonValue::JsonValue(bool Value)
{
    std::cout << "bool constructor" << std::endl;
    JsonType = EJsonType::Bool;
    BoolValue = Value;
}

JsonValue::JsonValue(double Value)
{
    std::cout << "double constructor" << std::endl;
    JsonType = EJsonType::Double;
    DoubleValue = Value;
}

JsonValue::JsonValue(int Value)
{
    std::cout << "int constructor" << std::endl;
    JsonType = EJsonType::Int;
    IntValue = Value;
}

JsonValue::JsonValue(const std::map<std::wstring, JsonValue*>& Value)
{
    std::cout << "object constructor" << std::endl;
    JsonType = EJsonType::Object;
    ObjectValue = new JsonObject(Value);
}

JsonValue::JsonValue(const std::vector<JsonValue*>& Value)
{
    std::cout << "array constructor" << std::endl;
    JsonType = EJsonType::Array;
    ArrayValue = new JsonArray(Value);
}

JsonValue::JsonValue(const JsonValue& Value)
{
    std::cout << "copy constructor" << std::endl;

}

JsonValue::JsonValue(const JsonValue&& Value)
{
    std::cout << "move constructor" << std::endl;
}

bool JsonValue::IsObject()
{
    return JsonType == EJsonType::Object;
}

bool JsonValue::IsString()
{
    return JsonType == EJsonType::String;
}

bool JsonValue::IsBool()
{
    return JsonType == EJsonType::Bool;
}

bool JsonValue::IsArray()
{
    return JsonType == EJsonType::Array;
}

const JsonObject& JsonValue::AsObject() const
{
    return *ObjectValue;
}

const std::wstring& JsonValue::AsString() const
{
    return *StringValue;
}

const bool JsonValue::AsBool() const
{
    return BoolValue;
}

const JsonArray& JsonValue::AsArray() const
{
    return *ArrayValue;
}

std::wstring JsonValue::Stringify() const
{
    std::wstring Result;

    switch (JsonType)
    {
        case EJsonType::Int:
        {
            std::wostringstream ws;
            ws << IntValue;
            Result = ws.str();
            break;
        }
        case EJsonType::Double:
        {
            std::wostringstream ws;
            ws << DoubleValue;
            Result = ws.str();
            break;
        }
        case EJsonType::Null:
        {
            Result = L"null";
            break;
        }
        case EJsonType::String:
        {
            Result = *StringValue;
            break;
        }
        case EJsonType::Bool:
        {
            Result = BoolValue ? L"true" : L"false";
            break;
        }
        case EJsonType::Object:
        {
            Result += L"{";
            JsonObject::iterator Iter;
            Iter = ObjectValue->begin();
            while (Iter != ObjectValue->end())
            {
                Result += Iter->first;
                Result += L":";
                Result += Iter->second->Stringify();
                
                if (++Iter != ObjectValue->end())
                {
                    Result += L",";
                }
            }
            Result += L"}";
            break;
        }
        case EJsonType::Array:
        {
            Result += L"[";
            JsonArray::iterator Iter;
            Iter = ArrayValue->begin();
            while (Iter != ArrayValue->end())
            {
                Result += (*Iter)->Stringify();
                if (++Iter != ArrayValue->end())
                {
                    Result += L",";
                }
            }
            Result += L"]";
            break;
        }
    }

    return Result;
}

std::vector<std::wstring> JsonValue::ObjectKeys() const
{
    std::vector<std::wstring> Keys;

    if (JsonType == EJsonType::Object)
    {
        JsonObject::const_iterator iter = ObjectValue->begin();
        while (iter != ObjectValue->end())
        {
            Keys.push_back(iter->first);

            iter++;
        }
    }

    return Keys;
}

JsonValue* JsonValue::Child(const wchar_t* Key) const
{
    if (JsonType == EJsonType::Object)
    {
        JsonObject::const_iterator Iter = ObjectValue->find(Key);
        if (Iter != ObjectValue->end())
        {
            return Iter->second;
        }
    }

    return nullptr;
}