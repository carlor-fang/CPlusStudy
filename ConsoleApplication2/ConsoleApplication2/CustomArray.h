#include <iostream>

#pragma once
template<typename T>
class CustomArray
{
public:
    CustomArray();
    CustomArray(const CustomArray& ca);
    ~CustomArray();

    int getCurNumber() const { return curNumber; }
    int getMaxNumber() const { return maxNumber; }

    void reserve(int count);

    void push(const T& value);
    void insert(int index, const T& value);
    void pop();
    void remove(int index);
    int findIndex(const T& value);
    void clear();

    void print();
private:
    T* datas;
    int maxNumber;
    int curNumber;
};
