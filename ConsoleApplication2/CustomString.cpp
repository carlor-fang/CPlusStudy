#include "CustomString.h"
#include <vector>

CustomString::CustomString()
{
    emptyMem();
}

CustomString::CustomString(const char* value)
{
    if (!value) {
        emptyMem();
        return;
    }

    int length = strlen(value);
    p = (char*)malloc(sizeof(char) * (length + 1));
    if (p) {
        memcpy(p, value, sizeof(char) * length);
        p[length] = 0;
    }
}

CustomString::CustomString(const char* value, int startIndex, int count)
{
    if (!value) {
        emptyMem();
        return;
    }
    if (startIndex < 0) {
        startIndex = 0;
    }
    int length = strlen(value);
    if (startIndex + count > length) {
        count = length - startIndex;
    }

    p = (char*)malloc(sizeof(char) * (count + 1));
    if (p) {
        auto temp = &value[startIndex];
        memcpy(p, temp, count);
        p[count] = 0;
    }
}
CustomString::CustomString(const CustomString& cs)
    : CustomString(*cs)
{
}

CustomString::~CustomString()
{
    free(p);
}

void CustomString::emptyMem()
{
    p = (char*)malloc(sizeof(char));
    if (p) {
        p[0] = 0;
    }
}

char* CustomString::operator*() const {
    return p;
}

void CustomString::operator=(const char* value) {
    if (!value) {
        return;
    }

    int newLen = strlen(value);
    char* newMem = (char*)realloc(p, sizeof(char) * (newLen + 1));
    if (newMem) {
        p = newMem;
        memcpy(p, value, sizeof(char) * newLen);
        p[newLen] = 0;
    }
}

bool CustomString::operator==(CustomString& cs) const {
    if (cs.len() != len()) {
        return false;
    }

    int index = 0;
    while (p[index] && cs[index] && p[index] == cs[index]) {
        index++;
    }
    return index == len();
}

char CustomString::operator[](int index) {
    if (index < len()) {
        return p[index];
    }
    return 0;
}
int CustomString::len() const
{
    if (p) {
        return strlen(p);
    }
    return 0;
}

CustomString CustomString::sub(const int index, const int count)
{
    int length = len();
    if (length <= index || index < 0 || count <= 0 || index + count > length) {
        return nullptr;
    }


    return CustomString(p, index, count);
}

void CustomString::append(const char* value)
{
    if (!value) {
        return;
    }
    int oldLen = len();
    int addLen = strlen(value);
    char* newMem = (char*)realloc(p, sizeof(char) * (oldLen + addLen + 1));
    if (newMem) {
        p = newMem;
        char* temp = &p[oldLen];
        memcpy(temp, value, sizeof(char) * addLen);
        p[oldLen + addLen] = 0;
    }
}

int CustomString::find(const char* value, int findIndex)
{
    int index = 0;
    int resultIndex = 0;
    int ret = -1;

    auto src = p;
    auto subchars = value;

    while (*subchars) {
        while (*subchars && *src) {
            if (*subchars == *src) {
                if (ret < 0) {
                    ret = index;
                }
                subchars++;
                src++;
            }
            else {
                ret = -1;
                src++;
                subchars = value;
            }
            index++;
        }
        if (ret < 0) {
            break;
        }
        if (resultIndex == findIndex) {
            break;
        }

        resultIndex++;
        subchars = value;
    }

    return ret;
}

int CustomString::findCount(const char* value)
{
    int index = 0;
    int ret = 0;
    int pos = find(value, index);
    while (pos >= 0) {
        ret++;
        pos = find(value, ++index);
    }

    return ret;
}

CustomString* CustomString::split(const char* value)
{
    int count = findCount(value);
    if (count == 0) {
        return this;
    }

    CustomString* ret = new CustomString[count + 1]();

    int index = 0;
    int startPos = 0;
    int endPos = find(value, index);
    while (endPos >= 0) {
        CustomString* temp = &ret[index];
        ret[index] = *(new(temp) CustomString(p, startPos, endPos - startPos));

        startPos = endPos + 1;
        endPos = find(value, ++index);
    }
    CustomString* temp = &ret[index];
    ret[index] = *(new(temp) CustomString(p, startPos + 1, len() - startPos - 1));

    return ret;    
}

void CustomString::print()
{
    if (p) {
        std::cout << p << std::endl;
    }
}
