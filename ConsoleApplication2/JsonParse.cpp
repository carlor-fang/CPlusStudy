#include "JsonParse.h"
#include <cctype>
#include <array>
#include <comdef.h>
#include <map>
#include <vector>


bool JsonParse::ExcludeUnusefulChar(const wchar_t **Value)
{
    wchar_t Temp = **Value;
    while (**Value == L' ' || **Value == L'\t' || **Value == L'\v' || **Value == L'\n' || **Value == L'\r')
        (*Value)++;

    return **Value != 0;
}

JsonValue* JsonParse::Parse(const wchar_t* Value)
{
    if (!Value) 
    {
        return nullptr;
    }

    if (!ExcludeUnusefulChar(&Value))
    {
        return nullptr;
    }

    if (*Value == L'{')
    {
        return ParseObject(&Value);
    }
    else if (*Value == L'[')
    {
        return ParseArray(&Value);
    }
    else
    {
        return nullptr;
    }
}

JsonValue* JsonParse::ParseValue(const wchar_t **Value)
{
    switch(**Value)
    {
        case '"':
            {
                std::wstring StringValue;
                if (!ParseString(Value, StringValue))
                {
                    return nullptr;
                }
                return new JsonValue(StringValue);
            }
        case '{':
            return ParseObject(Value);
        case '[':
            return ParseArray(Value);
        default:
            return ParseNumberOrBoolean(Value);
    }

}

JsonValue* JsonParse::ParseObject(const wchar_t **Value)
{
    // 去{
    (*Value)++;

    std::map<std::wstring, JsonValue*> Object;
    auto FreeJsonValueMap = [&Object]()
    {
        std::map<std::wstring, JsonValue*>::iterator Iter;
        for (Iter = Object.begin(); Iter != Object.end(); Iter++)
        {
            delete (*Iter).second;
        }
    };

    while (**Value != 0)
    {
        if (!ExcludeUnusefulChar(Value))
        {
            goto ReturnNull;
        }
        if (**Value == L'}')
        {
            (*Value)++;
            return new JsonValue(Object);
        }
        // key
        if (**Value != L'"')
        {
            goto ReturnNull;
        }
        std::wstring Key;
        if (!ParseString(Value, Key))
        {
            goto ReturnNull;
        }

        // :
        if (!ExcludeUnusefulChar(Value))
        {
            goto ReturnNull;
        }
        if (**Value != L':')
        {
            goto ReturnNull;
        }
        (*Value)++;
        if (!ExcludeUnusefulChar(Value))
        {
            goto ReturnNull;
        }
        JsonValue* Data = ParseValue(Value);
        if (!Data)
        {
            goto ReturnNull;
        }
        Object[Key] = Data;
        if (!ExcludeUnusefulChar(Value))
        {
            break;
        }
        if (**Value == L',')
        {
            (*Value)++;
        }
    }

    return new JsonValue(Object);
ReturnNull:
    FreeJsonValueMap();
    return nullptr;    
}

JsonValue* JsonParse::ParseArray(const wchar_t **Value)
{
    // 去[
    (*Value)++;
    
    std::vector<JsonValue*> Array;
    auto FreeJsonValueArray = [&Array]()
    {
        while (Array.size() > 0)
        {
            delete Array.at(0);
        }
    };

    while (**Value != 0)
    {
        if (!ExcludeUnusefulChar(Value))
        {
            goto ReturnNull;
        }
        if (**Value == L']')
        {
            (*Value)++;
            return new JsonValue(Array);
        }
        JsonValue* Data = ParseValue(Value);
        if (!Data)
        {
            goto ReturnNull;
        }
        Array.push_back(Data);
        if (!ExcludeUnusefulChar(Value))
        {
            break;
        }
        if (**Value == L',')
        {
            (*Value)++;
        }
    }

    return new JsonValue(Array);

ReturnNull:
    FreeJsonValueArray();
    return nullptr;
}

JsonValue* JsonParse::ParseNumberOrBoolean(const wchar_t** Value)
{
    if (_wcsnicmp(*Value, L"true", 4) == 0)
    {
        (*Value) += 4;
        return new JsonValue(true);

    }
    else if (_wcsnicmp(*Value, L"false", 5) == 0)
    {
        (*Value) += 5;
        return new JsonValue(false);
    }
    else if (_wcsnicmp(*Value, L"null", 4) == 0)
    {
        (*Value) += 4;
        return new JsonValue();
    }
    else if (**Value == '-' || **Value >= '0' && **Value <= '9')
    {
        int Symbol = 1;
        if (**Value == '-')
        {
            Symbol = -1;
            (*Value)++;
        }
        double Number = 0;
        while (**Value >= '0' && **Value <= '9')
        {
            Number = Number * 10 + (**Value - '0');
            (*Value)++;
        }
        if (**Value == '.')
        {
            (*Value)++;
            double Decimal = 0.1f;
            int DecimalCount = 0;
            while (**Value >= '0' && **Value <= '9')
            {
                DecimalCount++;
                double Temp = (**Value - '0') * pow(0.1, DecimalCount);
                Number += Temp;
                (*Value)++;
            }
        }
        if (**Value == 'e' || **Value == 'E')
        {
            (*Value)++;
            bool Neg = false;
            if (**Value == '-')
            {
                (*Value)++;
                Neg = true;
            }
            else if (**Value == '+')
            {
                (*Value)++;
            }
            int IndexValue = 0;
            while (**Value >= '0' && **Value <= '9')
            {
                IndexValue = IndexValue * 10 + (**Value - '0');
                (*Value)++;
            }
            Number = Number * pow(10, Neg ? -1 * IndexValue : IndexValue);
        }
        Number *= Symbol;
        if (abs((Number) - floor(Number)) <= 0.000001)
        {
            int IntValue = floor(Number);
            return new JsonValue(IntValue);
        }
        else
        {
            return new JsonValue(Number);
        }
    }
}

bool JsonParse::ParseString(const wchar_t** Value, std::wstring& OutString)
{
    // 假定string中间的引号前后有"//"
    int QuoteCount = 0;
    while (**Value != 0)
    {
        if (**Value == L'\\')
        {
            (*Value)++;
            
            OutString += **Value;
        }
        else if (**Value == L'"')
        {
            if (++QuoteCount == 2)
            {
                (*Value)++;
                return true;
            }
        }
        else 
        {
            OutString += **Value;
        }
        (*Value)++;
    }

    return false;
}