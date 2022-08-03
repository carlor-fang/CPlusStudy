#pragma once
#include <map>
#include <string>
#include <iostream>

using namespace std;

template<typename T>
class BindClassFiled
{
private:
    unsigned long Offset;
    string Key;
public:
    BindClassFiled(string InKey, unsigned long InOffset) : Key(InKey), Offset(InOffset){}
    BindClassFiled(const BindClassFiled& InBindClassFiled)
    {
        this->Offset = InBindClassFiled.Offset;
        this->Key = InBindClassFiled.Key;
    }
public:
    template<typename VT>
    VT* Get(T* Obj)
    {
        return (VT*)((unsigned char*)Obj + Offset);
    }
};


class TestClassA
{
public:
    int p1 = 1;
    bool p2 = false;
    string p3 = "p33333333";

    void Test1(void* params)
    {
        std::cout << "test1" << std::endl;
    }
    static void Test2(void* params)
    {
        std::cout << "test2" << std::endl;
    }
};

using ClassFunc = void(__cdecl TestClassA::*)(void*);
using StaticFunc = void(__cdecl *)(void*);

template<typename T>
class Binder
{
public:
    void BindVar(string Key, unsigned long Offset)
    {
        BindClassFiled<T> Field(Key, Offset);
        FieldMap.insert(pair<string, BindClassFiled<T>>(Key, Field));
    }

    template<typename VT>
    VT* FindVar(T* Obj, string Key)
    {
        auto Itr = FieldMap.find(Key);
        if (Itr == FieldMap.end())
        {
            return nullptr;
        }
        //
        BindClassFiled<T> Field = Itr->second;
        return Field.Get<VT>(Obj);
    }

    void BindFunc(string Key, ClassFunc Func)
    {
        ClassFuncMap.insert(pair<string, ClassFunc>(Key, Func));
    }

    void CallFunc(T* Obj, string Key, void* Param)
    {
        auto Itr = ClassFuncMap.find(Key);
        if (Itr == ClassFuncMap.end())
        {
            return;
        }
        ClassFunc Func = Itr->second;
        (Obj->*Func)(Param);
    }

    void BindStaticFunc(string Key, StaticFunc Func)
    {
        StaticFuncMap.insert(pair<string, StaticFunc>(Key, Func));
    }

    void CallStaticFunc(string Key, void* Param)
    {
        auto Itr = StaticFuncMap.find(Key);
        if (Itr == StaticFuncMap.end())
        {
            return;
        }
        StaticFunc Func = Itr->second;
        Func(Param);
    }
private:
    map<string, BindClassFiled<T>> FieldMap;
    map<string, ClassFunc> ClassFuncMap;
    map<string, StaticFunc> StaticFuncMap;
};
