// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "TabDataBase.h"
#include "CompressTabFileBase.h"
#include <string>

#define TAB_FILE_DATA(TabDataClass)\
class TabDataClass : public TabDataBase<TabDataClass>

#define TAB_FILE_WITH_PATH(TabFileClass, TabDataClass)\
class TabFileClass : public CompressTabFileBase<TabFileClass, TabDataClass::TabKeyType, TabDataClass>\
{\
};

#define TAB_FILE_DATA_SINGLE_KEY(KeyType, Key)\
public:\
    typedef KeyType TabKeyType;\
    const KeyType& GetKey()\
    {\
        return Key;\
    }\


#define TAB_FILE_DATA_REGISTER(FieldValue, FieldName)\
    RegisterField(FieldName, offsetof(TabDataClass, FieldValue), FieldValue);