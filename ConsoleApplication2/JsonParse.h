#pragma once
#include <string.h>
#include <iostream>
#include "assert.h"
#include "JsonValue.h"

//1[]�����Ŵ������һ�����飻
//2 {}�����Ŵ������һ������
//3 ˫���š�����ʾ��������ֵ
//4 ð�ţ��������ǰ��֮��Ĺ�ϵ��ð��ǰ�������Ե����ƣ����������Ե�ֵ�����ֵ�����ǻ����������ͣ�Ҳ�����������������͡�

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

