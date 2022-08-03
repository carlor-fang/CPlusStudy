#pragma once
#include <string.h>
#include <iostream>
#include "assert.h"
#include "JsonValue.h"

//1[]中括号代表的是一个数组；
//2 {}大括号代表的是一个对象
//3 双引号“”表示的是属性值
//4 冒号：代表的是前后之间的关系，冒号前面是属性的名称，后面是属性的值，这个值可以是基本数据类型，也可以是引用数据类型。

class JsonParse
{
public:
    static JsonValue* Parse(const wchar_t* Value);
private:
    static bool ExcludeUnusefulChar(const wchar_t **Value);
    static JsonValue* ParseObject(const wchar_t **Value);
    static JsonValue* ParseArray(const wchar_t **Value);
    static bool ParseString(const wchar_t **Value, std::wstring& OutString);
    static JsonValue* ParseValue(const wchar_t **Value);
    static JsonValue* ParseNumberOrBoolean(const wchar_t** Value);
};

