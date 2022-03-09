#pragma once
#include <iostream>

class CustomString
{
private: 
    void emptyMem();
public:
    CustomString();

    CustomString(const char* value);
    CustomString(const char* value, int startIndex, int count);

    CustomString(const CustomString& cs);

    ~CustomString();

    int len() const;

    CustomString sub(int index, int count);

    void append(const char* value);

    int find(const char* value, int findIndex = 0);

    int findCount(const char* value);

    CustomString* split(const char* value);

    void print();

    char* operator*() const;

    void operator=(const char* value);

    bool operator==(CustomString& cs) const;

    char operator[](int index);
private:
    char* p = nullptr;
};