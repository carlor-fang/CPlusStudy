// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "KTabDataBase.h"
#include "KTabFileBase.h"

#define TAB_FILE_DATA(TabDataClass)\
class TabDataClass : public FKTabDataBase<TabDataClass>

#define TAB_FILE_WITH_PATH(TabFileClass, TabDataClass, FilePath)\
class TabFileClass : public FKTabFileBase<TabFileClass, TabDataClass::TabKeyType, TabDataClass>\
{\
public:\
    TabFileClass()\
    {\
        Load(FilePath);\
    }\
};\
TabFileClass TabFileClass##Instance = TabFileClass::Get();\

#define TAB_FILE_DATA_SINGLE_KEY(KeyType, Key)\
public:\
    typedef KeyType TabKeyType;\
    const KeyType& GetKey()\
    {\
        return Key;\
    }\


#define TAB_FILE_DATA_REGISTER(FieldValue, FieldName)\
    RegisterField(FieldName, offsetof(TabDataClass, FieldValue), FieldValue);