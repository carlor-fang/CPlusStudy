#pragma once
#include <iostream>
#include <map>
#include <vector>

enum class EJsonType
{
    Int = 1,
    Double,
    Null,
    String,
    Bool,
    Object,
    Array,
};

class JsonValue;

typedef std::map<std::wstring, JsonValue*> JsonObject;
typedef std::vector<JsonValue*> JsonArray;

class JsonValue
{
public:
    JsonValue();
    JsonValue(const std::wstring& Value);
    JsonValue(const wchar_t* Value);
    JsonValue(bool Value);
    JsonValue(int Value);
    JsonValue(double Value);
    JsonValue(const std::map<std::wstring, JsonValue*>& Value);
    JsonValue(const std::vector<JsonValue*>& Value);

    JsonValue(const JsonValue& Value);
    JsonValue(const JsonValue&& Value);

    ~JsonValue();

    bool IsObject();
    bool IsString();
    bool IsBool();
    bool IsArray();

    const JsonObject& AsObject() const;
    const std::wstring& AsString() const;
    const bool AsBool() const;
    const JsonArray& AsArray() const;
    std::wstring Stringify() const;

    std::vector<std::wstring> ObjectKeys() const;
    JsonValue* Child(const wchar_t* Key) const;
private:
    EJsonType JsonType;
    union
    {
        int IntValue;
        double DoubleValue;
        bool BoolValue;
        std::wstring* StringValue;
        JsonObject* ObjectValue;
        JsonArray* ArrayValue;
    };
};

