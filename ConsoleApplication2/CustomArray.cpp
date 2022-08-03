#include "CustomArray.h"

template<typename T>
CustomArray<T>::CustomArray()
{
    curNumber = 0;
    maxNumber = 0;
    datas = nullptr;
}

template<typename T>
CustomArray<T>::CustomArray(const CustomArray& ca)
{
    reserve(ca.getMaxNumber());
    curNumber = ca.getCurNumber();
    for (int i = 0; i < curNumber; i++) {
        datas[i] = ca[i];
    }
}

template<typename T>
CustomArray<T>::~CustomArray()
{
    curNumber = 0;
    maxNumber = 0;
    if (datas)
    {
        delete[]datas;
        datas = nullptr;
    }
}

template<typename T>
void CustomArray<T>::reserve(int newNumber)
{
    if (newNumber < maxNumber) {
        return;
    }
    T* temp = new T[newNumber]();
    for (int i = 0; i < curNumber; i++) {
        temp[i] = datas[i];
    }
    if (datas)
    {
        delete[] datas;
    }
    datas = temp;

    maxNumber = newNumber;
}

template<typename T>
void CustomArray<T>::push(const T& value)
{
    insert(curNumber, value);
}

template<typename T>
void CustomArray<T>::insert(int index, const T& value)
{
    if (index < 0) {
        index = 0;
    }
    else if (index >= curNumber) {
        index = curNumber;
    }

    if (maxNumber < curNumber + 1) {
        reserve((curNumber + 1) * 2);
    }

    int curIndex = curNumber;
    while (curIndex > index) {
        datas[curIndex] = datas[curIndex - 1];
        curIndex--;
    }

    curNumber++;
    T* temp = &datas[index];
    new(temp) T(value);
}

template<typename T>
void CustomArray<T>::pop()
{
    remove(0);
}

template<typename T>
void CustomArray<T>::remove(int index)
{
    if (index < 0 || index >= curNumber) {
        return;
    }

    T* temp = &datas[index];
    temp->~T();
    curNumber--;

    int curIndex = index;
    while (curIndex < curNumber) {
        datas[curIndex] = datas[curIndex + 1];
        curIndex++;
    }
}

template<typename T>
int CustomArray<T>::findIndex(const T& value)
{
    if (curNumber <= 0) {
        return -1;
    }

    T temp = std::move(value);

    int size = sizeof(value);
    int index = 0;
    while (index < curNumber) {
        if (datas[index] == temp) {
            break;
        }
        index++;
    }
    if (index < curNumber) {
        return index;
    }
    else {
        return -1;
    }
}

template<typename T>
void CustomArray<T>::clear()
{
    while (curNumber > 0) {
       remove(curNumber - 1);
    }
}

template<typename T>
void CustomArray<T>::print()
{
    std::cout << "start" << std::endl;

    for (int i = 0; i < curNumber; i++) {
        std::cout << &datas[i] << std::endl;
    }

    std::cout << "end" << std::endl;
}